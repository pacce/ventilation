#ifndef VENTILATION_MODES_VCV_HPP__
#define VENTILATION_MODES_VCV_HPP__

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
    class VCV : public Base<Precision> {
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

#endif // VENTILATION_MODES_VCV_HPP__
