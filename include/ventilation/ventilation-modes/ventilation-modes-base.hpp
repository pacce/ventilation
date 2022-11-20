#ifndef VENTILATION_MODES_BASE_HPP__
#define VENTILATION_MODES_BASE_HPP__

#include <chrono>

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
    class Base {
        public:
            virtual ~Base() {}

            Packet<Precision>
            operator()(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step) {
                return this->stimulate(lung, step);
            }
        private:
            virtual Packet<Precision>
            stimulate(const lung::Forward<Precision>& lung, const std::chrono::duration<Precision>& step);
    };
} // namespace modes
} // namespace ventilation

#endif // VENTILATION_MODES_BASE_HPP__
