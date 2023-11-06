#ifndef VENTILATION_MODES_HPP__
#define VENTILATION_MODES_HPP__

#include <optional>
#include <variant>

#include "ventilation/ventilation-flow.hpp"
#include "ventilation/ventilation-pressure.hpp"
#include "ventilation/ventilation-volume.hpp"

#include "ventilation/ventilation-packet.hpp"

#include "ventilation/ventilation-control.hpp"
#include "ventilation/ventilation-cycle.hpp"
#include "ventilation/ventilation-integration.hpp"
#include "ventilation/ventilation-lung.hpp"

#include "ventilation/ventilation-time.hpp"

namespace ventilation {
namespace modes {
    template <typename Precision>
    class PCV {
        using Gain = control::Gain<Precision, Pressure>;
        public:
            PCV(
                      const PEEP<Precision>&            peep
                    , const pressure::Peak<Precision>&  peak
                    , const cycle::Cycle<Precision>&    cycle
               )
                : peep_(peep)
                , peak_(peak)
                , cycle_(cycle)
                , control_(Gain(5e-3), Gain(6e-5), peak_)
            {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                return this->stimulate(lung, step);
            }

            void set(const pressure::Peak<Precision>& peak) { peak_ = peak; }
            void set(const PEEP<Precision>& peep)           { peep_ = peep; }
            void set(const cycle::Cycle<Precision>& cycle)  { cycle_ = cycle; }

            const PEEP<Precision>& peep() const             { return peep_; }
            const pressure::Peak<Precision>& peak() const   { return peak_; }
            const cycle::Cycle<Precision>& cycle() const    { return cycle_; }
        private:
            Packet<Precision>
            stimulate(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                std::optional<cycle::Mark> mark = cycle_(step);
                if (not mark) {
                } else if (*mark == cycle::Mark::START_OF_INSPIRATION) {
                    control_.set(peak_);
                    control_.clear();
                } else if (*mark == cycle::Mark::START_OF_EXPIRATION) {
                    control_.set(peep_);
                    control_.clear();
                }

                switch(cycle_.state()) {
                    case cycle::State::INSPIRATION:
                    case cycle::State::EXPIRATION:
                        return breathe(lung, step);
                    case cycle::State::INSPIRATORY_PAUSE:
                    case cycle::State::EXPIRATORY_PAUSE:
                        return pause(lung, step);
                    default:
                        return {Flow<Precision>(), Pressure<Precision>(), Volume<Precision>()};
                }
            }

            Packet<Precision>
            breathe(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                current_.flow       = estimate(current_.pressure);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>
            pause(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                current_.flow       = Flow<Precision>();
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Flow<Precision>
            estimate(const Pressure<Precision>& current) {
                Flow<Precision> extreme(0.6);
                return std::min(control_(current), extreme);
            }

            PEEP<Precision>                 peep_;
            pressure::Peak<Precision>       peak_;
            Packet<Precision>               current_;

            cycle::Cycle<Precision>         cycle_;

            Control<Precision, Pressure>    control_;
    };

    template <typename Precision>
    class VCV {
        template <template <typename> typename Target>
        using Gain = control::Gain<Precision, Target>;
        public:
            VCV(
                      const PEEP<Precision>&            peep
                    , const volume::Tidal<Precision>&   tidal
                    , const cycle::Cycle<Precision>&    cycle
               )
                : cycle_(cycle)
                , offset_(Volume<Precision>())
                , inspiration_(Gain<Volume>(5e-3), Gain<Volume>(6e-4), tidal)
                , expiration_(Gain<Pressure>(5e-3), Gain<Pressure>(6e-5), peep)
            {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                return this->stimulate(lung, step);
            }

            void set(const volume::Tidal<Precision>& tidal) { inspiration_.set(tidal); }
            void set(const PEEP<Precision>& peep)           { expiration_.set(peep); }
            void set(const cycle::Cycle<Precision>& cycle)  { cycle_ = cycle; }

            const cycle::Cycle<Precision>& cycle() const    { return cycle_; }
        private:
            Packet<Precision>
            stimulate(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                std::optional<cycle::Mark> mark = cycle_(step);
                if (not mark) {
                } else if (*mark == cycle::Mark::START_OF_INSPIRATION) {
                    offset_ = current_.volume;
                    inspiration_.clear();
                } else if (*mark == cycle::Mark::START_OF_EXPIRATION) {
                    expiration_.clear();
                }

                switch(cycle_.state()) {
                    case cycle::State::INSPIRATION:
                        return inspiration(lung, step);
                    case cycle::State::EXPIRATION:
                        return expiration(lung, step);
                    case cycle::State::INSPIRATORY_PAUSE:
                    case cycle::State::EXPIRATORY_PAUSE:
                        return pause(lung, step);
                    default:
                        return {Flow<Precision>(), Pressure<Precision>(), Volume<Precision>()};
                }
            }

            volume::Tidal<Precision>
            tidal() const {
                return volume::Tidal(current_.volume - offset_);
            }

            Packet<Precision>
            inspiration(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                Flow<Precision> extreme(10.0);
                Flow<Precision> actual = inspiration_(this->tidal());
                current_.flow       = std::min(actual, extreme);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>
            expiration(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                current_.flow       = expiration_(current_.pressure);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>
            pause(const lung::Forward<Precision>& lung, const Time<Precision>& step) {
                current_.flow       = Flow<Precision>();
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>       current_;
            cycle::Cycle<Precision> cycle_;

            ventilation::Volume<Precision>  offset_;
            Control<Precision, Volume>      inspiration_;
            Control<Precision, Pressure>    expiration_;
    };
} // namespace modes

    template <typename Precision>
    using Modes = std::variant<
          modes::PCV<Precision>
        , modes::VCV<Precision>
        >;

namespace modes {
namespace visitor {
    template <typename Precision>
    struct Control {
        const lung::Forward<Precision>          lung;
        const Time<Precision>  step;

        Packet<Precision>
        operator()(PCV<Precision>& mode) const {
            return mode(lung, step);
        }

        Packet<Precision>
        operator()(VCV<Precision>& mode) const {
            return mode(lung, step);
        }
    };
} // namespace visitor
namespace setter {
    template <typename Precision>
    struct PEEP {
        const ventilation::PEEP<Precision> peep;

        void operator()(PCV<Precision>& mode) const { mode.set(peep); }
        void operator()(VCV<Precision>& mode) const { mode.set(peep); }
    };

    template <typename Precision>
    struct Peak {
        const ventilation::pressure::Peak<Precision> peak;

        void operator()(PCV<Precision>& mode) const { mode.set(peak); }
        void operator()(VCV<Precision>&) const {}
    };

    template <typename Precision>
    struct Flow {
        const ventilation::Flow<Precision> flow;

        void operator()(PCV<Precision>&) const {}
        void operator()(VCV<Precision>& mode) const { mode.set(flow); }
    };

    template <typename Precision>
    struct Cycle {
        const ventilation::cycle::Cycle<Precision> cycle;

        void operator()(PCV<Precision>& mode) const { mode.set(cycle); }
        void operator()(VCV<Precision>& mode) const { mode.set(cycle); }
    };
} // namespace setter
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
