#ifndef VENTILATION_MODES_HPP__
#define VENTILATION_MODES_HPP__

#include <chrono>

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"
#include "ventilation-packet.hpp"

#include "ventilation-control.hpp"
#include "ventilation-cycle.hpp"
#include "ventilation-integration.hpp"
#include "ventilation-lung.hpp"

namespace ventilation {
    template <typename Precision>
    class Mode {
        public:
            virtual ~Mode() {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                return this->stimulate(lung, step);
            }
        private:
            virtual Packet<Precision>
            stimulate(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step);
    };

namespace modes {
    template <typename Precision>
    class PCV : public Mode<Precision> {
        using Gain = control::Gain<Precision, Pressure>;
        public:
            PCV(
                      const PEEP<Precision>&            peep
                    , const pressure::Peak<Precision>&  peak
                    , cycle::Cycle<Precision>&          cycle
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

            PEEP<Precision>             peep_;
            pressure::Peak<Precision>   peak_;
            Packet<Precision>   current_;

            cycle::Cycle<Precision> cycle_;

            Control<Precision, Pressure> control_;
    };

    template <typename Precision>
    class VCV : public Mode<Precision> {
        template <template <typename> typename Target>
        using Gain = control::Gain<Precision, Target>;
        public:
            VCV(
                      const PEEP<Precision>&    peep
                    , const Flow<Precision>&    flow
                    , cycle::Cycle<Precision>&  cycle
               )
                : cycle_(cycle)
                , inspiration_(Gain<Flow>(5e-3), Gain<Flow>(6e-3), flow)
                , expiration_(Gain<Pressure>(5e-3), Gain<Pressure>(6e-5), peep)
            {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                return this->stimulate(lung, step);
            }
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
                return {Flow(0.0), Pressure(0.0), Volume(0.0)};
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
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
