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
                , control_(control::Gain<Precision>(1e-3), peak_)
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

                current_.flow       = control_(current_.pressure);
                current_.volume     += integration::square(1000.0 * current_.flow, step);
                current_.pressure   = lung.forward(current_.flow, current_.volume);

                return current_;
            }
        private:
            PEEP<Precision>     peep_;
            Pressure<Precision> peak_;
            Packet<Precision>   current_;

            cycle::State            state_;
            cycle::Cycle<Precision> cycle_;

            control::Proportional<Precision, Pressure>  control_;
    };
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_HPP__
