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
namespace modes {
    template <typename Precision>
    class PCV {
        using Gain = control::Gain<Precision, Pressure>;
        public:
            PCV(
                      const PEEP<Precision>&            peep
                    , const pressure::Peak<Precision>&  peak
                    , cycle::Cycle<Precision>&          cycle
               )
                : peep_(peep)
                , peak_(peak)
                , state_(cycle::State::INSPIRATION)
                , cycle_(cycle)
                , control_(Gain(5e-3), Gain(6e-5), peak_)
            {}

            Packet<Precision>
            operator()(const Lung<Precision>& lung, const std::chrono::duration<Precision>& step) {
                cycle::State state = cycle_(step);
                if (state != state_) {
                    switch(state) {
                        case ventilation::cycle::State::INSPIRATION:
                        { control_.set_target(peak_); break; }
                        case ventilation::cycle::State::EXPIRATION:
                        { control_.set_target(peep_); break; }
                    }
                    state_ = state;
                }

                current_.flow       = estimate(current_.pressure);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung.forward(current_.flow, current_.volume);

                return current_;
            }
        private:
            Flow<Precision>
            estimate(const Pressure<Precision>& current) {
                Flow<Precision> extreme(0.6);
                return std::min(control_(current), extreme);
            }
            PEEP<Precision>             peep_;
            pressure::Peak<Precision>   peak_;
            Packet<Precision>   current_;

            cycle::State            state_;
            cycle::Cycle<Precision> cycle_;

            Control<Precision, Pressure> control_;
    };

    template <typename Precision>
    class VCV {
        template <template <typename> typename Target>
        using Gain = control::Gain<Precision, Target>;
        public:
            VCV(
                      const PEEP<Precision>&    peep
                    , const Flow<Precision>&    flow
                    , cycle::Cycle<Precision>&  cycle
               )
                : state_(cycle::State::INSPIRATION)
                , cycle_(cycle)
                , inspiration_(Gain<Flow>(5e-3), Gain<Flow>(6e-3), flow)
                , expiration_(Gain<Pressure>(5e-3), Gain<Pressure>(6e-5), peep)
            {}

            Packet<Precision>
            operator()(const Lung<Precision>& lung, const std::chrono::duration<Precision>& step) {
                switch(cycle_(step)) {
                    case ventilation::cycle::State::INSPIRATION:
                    { current_.flow = inspiration_(current_.flow); break; }
                    case ventilation::cycle::State::EXPIRATION:
                    { current_.flow = expiration_(current_.pressure); break; }
                }
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung.forward(current_.flow, current_.volume);
                return current_;
            }
        private:
            Packet<Precision>   current_;

            cycle::State            state_;
            cycle::Cycle<Precision> cycle_;

            Control<Precision, Flow>        inspiration_;
            Control<Precision, Pressure>    expiration_;
    };
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
