#ifndef VENTILATION_CONTROL_HPP__
#define VENTILATION_CONTROL_HPP__

#include <numeric>
#include <vector>

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"
#include "ventilation-traits.hpp"

namespace ventilation {
namespace control {
    template <typename Precision, template <typename> typename T>
    class Gain {
        static_assert(is_airway_type<T<Precision>>::value);
        public:
            explicit Gain() : Gain(Precision()) {}
            explicit Gain(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Gain& p) {
                os << p.value_;
                return os;
            }

            friend T<Precision>
            operator*(const Gain<Precision, T>& lhs, const T<Precision>& rhs) {
                return lhs.value_ * rhs;
            }

            friend T<Precision>
            operator*(const T<Precision>& lhs, const Gain<Precision, T>& rhs) {
                return lhs * rhs.value_;
            }
        private:
            T<Precision> value_;
    };

    template <typename Precision, template <typename> typename Target>
    class Proportional {
        static_assert(is_airway_type<Target<Precision>>::value);
        public:
            Proportional(
                    const Gain<Precision, Target>&  gain
                    , const Target<Precision>&      target
                    )
                : gain_(gain)
                , target_(target)
            {}

            Flow<Precision>
            operator()(const Target<Precision>& current) {
                Precision value = static_cast<Precision>(gain_ * (target_ - current));
                return Flow(value);
            }

            void
            set(const Target<Precision>& target) { target_ = target; }
        private:
            Gain<Precision, Target> gain_;
            Target<Precision>       target_;
    };

    template <typename Precision, template <typename> typename Target>
    class Integral {
        static_assert(is_airway_type<Target<Precision>>::value);
        public:
            Integral(const Gain<Precision, Target>& gain, const Target<Precision>& target)
                : gain_(gain)
                , target_(target)
            {}

            Flow<Precision>
            operator()(const Target<Precision>& current) {
                errors_.push_back(target_ - current);
                Target<Precision> e = std::accumulate(errors_.begin(), errors_.end(), Target<Precision>());
                Precision value     = static_cast<Precision>(gain_ * e);
                return Flow(value);
            }

            void
            set(const Target<Precision>& target) { target_ = target; }

            void
            clear() { errors_.clear(); }
        private:
            Gain<Precision, Target> gain_;
            Target<Precision>       target_;

            std::vector<Target<Precision>> errors_;
    };

} // namespace control
    // PI control
    template <typename Precision, template <typename> typename Target>
    class Control {
        static_assert(is_airway_type<Target<Precision>>::value);
        using Gain          = control::Gain<Precision, Target>;
        using Proportional  = control::Proportional<Precision, Target>;
        using Integral      = control::Integral<Precision, Target>;

        public:
            Control(const Proportional& proportional, const Integral& integral)
                : proportional_(proportional)
                , integral_(integral)
            {}

            Control(const Gain& p, const Gain& i, const Target<Precision>& target)
                : proportional_(p, target)
                , integral_(i, target)
            {}

            Flow<Precision>
            operator()(const Target<Precision>& current) {
                return proportional_(current) + integral_(current);
            }

            void
            set(const Target<Precision>& target) {
                proportional_.set(target);
                integral_.set(target);
            }

            void
            clear() { integral_.clear(); }
        private:
            Proportional    proportional_;
            Integral        integral_;
    };
} // namespace ventilation

#endif // VENTILATION_CONTROL_HPP__
