#ifndef VENTILATION_LUNG_HPP__
#define VENTILATION_LUNG_HPP__

#include "ventilation-compliance.hpp"
#include "ventilation-elastance.hpp"
#include "ventilation-resistance.hpp"

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"

namespace ventilation {
    template <typename Precision>
    class Lung {
        public:
            Lung(const Resistance<Precision>& resistance, const Elastance<Precision>& elastance)
                : resistance_(resistance)
                , elastance_(elastance)
            {}

            Lung(const Resistance<Precision>& resistance, const Compliance<Precision>& compliance)
                : resistance_(resistance)
            {
                Precision c = static_cast<Precision>(compliance);
                elastance_  = Elastance(1.0 / c);
            }

            Pressure<Precision>
            forward(const Flow<Precision>& flow, const Volume<Precision>& volume) const {
                return flow * resistance_ + volume * elastance_;
            }
        private:
            Resistance<Precision>   resistance_;
            Elastance<Precision>    elastance_;
    };
} // namespace ventilation

#endif // VENTILATION_LUNG_HPP__
