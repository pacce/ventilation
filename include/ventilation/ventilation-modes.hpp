#ifndef VENTILATION_MODES_HPP__
#define VENTILATION_MODES_HPP__

#include <chrono>
#include <variant>

#include "ventilation/ventilation-flow.hpp"
#include "ventilation/ventilation-pressure.hpp"
#include "ventilation/ventilation-volume.hpp"

#include "ventilation/ventilation-packet.hpp"

#include "ventilation/ventilation-control.hpp"
#include "ventilation/ventilation-cycle.hpp"
#include "ventilation/ventilation-integration.hpp"
#include "ventilation/ventilation-lung.hpp"

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
            operator()(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
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
            stimulate(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                switch(cycle_(step)) {
                    case ventilation::cycle::State::START_OF_INSPIRATION:
                    { control_.set(peak_); control_.clear(); break; }
                    case ventilation::cycle::State::START_OF_EXPIRATION:
                    { control_.set(peep_); control_.clear(); break; }
                    default:
                    { break; }
                }

                current_.flow       = estimate(current_.pressure);
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
                    , const Flow<Precision>&            flow
                    , const cycle::Cycle<Precision>&    cycle
               )
                : cycle_(cycle)
                , inspiration_(Gain<Flow>(5e-3), Gain<Flow>(6e-3), flow)
                , expiration_(Gain<Pressure>(5e-3), Gain<Pressure>(6e-5), peep)
            {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                return this->stimulate(lung, step);
            }

            void set(const Flow<Precision>& flow) { inspiration_.set(flow); }
            void set(const PEEP<Precision>& peep) { expiration_.set(peep); }
            void set(const cycle::Cycle<Precision>& cycle)  { cycle_ = cycle; }

            const cycle::Cycle<Precision>& cycle() const    { return cycle_; }
        private:
            Packet<Precision>
            stimulate(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                switch(cycle_(step)) {
                    case ventilation::cycle::State::INSPIRATION:
                    { return inspiration(lung, step); }
                    case ventilation::cycle::State::EXPIRATION:
                    { return expiration(lung, step); }
                    case ventilation::cycle::State::START_OF_INSPIRATION:
                    { inspiration_.clear(); return inspiration(lung, step); }
                    case ventilation::cycle::State::START_OF_EXPIRATION:
                    { expiration_.clear(); return expiration(lung, step); }
                }
                return {Flow<Precision>(0.0), Pressure<Precision>(0.0), Volume<Precision>(0.0)};
            }

            Packet<Precision>
            inspiration(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                current_.flow       = inspiration_(current_.flow);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>
            expiration(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                current_.flow       = expiration_(current_.pressure);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung(current_.flow, current_.volume);
                return current_;
            }

            Packet<Precision>   current_;
            cycle::Cycle<Precision> cycle_;

            Control<Precision, Flow>        inspiration_;
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
        const std::chrono::duration<Precision>  step;

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
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
