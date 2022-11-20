#ifndef VENTILATION_LUNG_HPP__
#define VENTILATION_LUNG_HPP__

#include "ventilation-compliance.hpp"
#include "ventilation-elastance.hpp"
#include "ventilation-resistance.hpp"

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"

namespace ventilation {
namespace lung {
    template <typename Precision>
    class Forward {
        public:
            Forward(const Resistance<Precision>& resistance, const Elastance<Precision>& elastance)
                : resistance_(resistance)
                , elastance_(elastance)
            {}

            Forward(const Resistance<Precision>& resistance, const Compliance<Precision>& compliance)
                : resistance_(resistance)
            {
                Precision c = static_cast<Precision>(compliance);
                elastance_  = Elastance(1.0 / c);
            }

            Pressure<Precision>
            operator()(const Flow<Precision>& flow, const Volume<Precision>& volume) const {
                return flow * resistance_ + volume * elastance_;
            }

            const Resistance<Precision>&
            resistance() const { return resistance_; }

            const Elastance<Precision>&
            elastance() const { return elastance_; }
        private:
            Resistance<Precision>   resistance_;
            Elastance<Precision>    elastance_;
    };
} // namespace lung
} // namespace ventilation

#endif // VENTILATION_LUNG_HPP__
