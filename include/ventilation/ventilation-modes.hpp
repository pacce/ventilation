#ifndef VENTILATION_MODES_HPP__
#define VENTILATION_MODES_HPP__

#include <chrono>

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"

#include "ventilation-control.hpp"
#include "ventilation-cycle.hpp"
#include "ventilation-lung.hpp"

namespace ventilation {
namespace modes {
    template <typename Precision>
    using PEEP = Pressure<Precision>;

    template <typename Precision>
    struct Packet {
        Flow<Precision>        flow;
        Pressure<Precision>    pressure;
        Volume<Precision>      volume;

        friend std::ostream&
        operator<<(std::ostream& os, const Packet<Precision>& packet) {
            os  << packet.pressure
                << ", "
                << packet.flow
                << ", "
                << packet.volume
                ;
            return os;
        }
    };

    template <typename Precision>
    class PCV {
        public:
            PCV(
                    const PEEP<Precision>&          peep
                    , const Pressure<Precision>&    peak
                    , cycle::Cycle<Precision>&      cycle
               )
                : peep_(peep)
                , peak_(peak)
                , state_(cycle::State::INSPIRATION)
                , cycle_(cycle)
                , proportional_(control::Gain<Precision>(7e-2), peak_)
                , integral_(control::Gain<Precision>(1e-3), peak_)
            {}

            Packet<Precision>
            operator()(const Lung<Precision>& lung, const std::chrono::duration<Precision>& step) {
                cycle::State state = cycle_(step);
                if (state != state_) {
                    switch(state) {
                        case ventilation::cycle::State::INSPIRATION:
                        { set_target(peak_); break; }
                        case ventilation::cycle::State::EXPIRATION:
                        { set_target(peep_); break; }
                    }
                    state_ = state;
                }

                current_.flow       = estimate(current_.pressure);
                current_.volume     += integration::square(current_.flow, step);
                current_.pressure   = lung.forward(current_.flow, current_.volume);

                return current_;
            }
        private:
            void
            set_target(const Pressure<Precision>& target) {
                proportional_.set_target(target);
                integral_.set_target(target);
            }

            Flow<Precision>
            estimate(const Pressure<Precision>& current) {
                return proportional_(current) + integral_(current);
            }
            PEEP<Precision>     peep_;
            Pressure<Precision> peak_;
            Packet<Precision>   current_;

            cycle::State            state_;
            cycle::Cycle<Precision> cycle_;

            control::Proportional<Precision, Pressure>  proportional_;
            control::Integral<Precision, Pressure>      integral_;
    };
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
