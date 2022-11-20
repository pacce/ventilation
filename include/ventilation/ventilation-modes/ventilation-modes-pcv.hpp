#ifndef VENTILATION_MODES_PCV_HPP__
#define VENTILATION_MODES_PCV_HPP__

#include <chrono>

#include "ventilation/ventilation-flow.hpp"
#include "ventilation/ventilation-pressure.hpp"
#include "ventilation/ventilation-volume.hpp"
#include "ventilation/ventilation-packet.hpp"

#include "ventilation/ventilation-control.hpp"
#include "ventilation/ventilation-cycle.hpp"
#include "ventilation/ventilation-integration.hpp"
#include "ventilation/ventilation-lung.hpp"
#include "ventilation-modes-base.hpp"

namespace ventilation {
namespace modes {
    template <typename Precision>
    class PCV : public Base<Precision> {
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
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_PCV_HPP__
