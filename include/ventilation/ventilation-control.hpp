#ifndef VENTILATION_CONTROL_HPP__
#define VENTILATION_CONTROL_HPP__

#include <boost/circular_buffer.hpp>
#include <numeric>

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"
#include "ventilation-traits.hpp"

namespace ventilation {
namespace control {
    template <typename Precision>
    class Gain {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Gain() : Gain(Precision()) {}
            explicit Gain(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Gain& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            friend Flow<Precision>
            operator*(const Gain<Precision>& lhs, const Flow<Precision>& rhs) {
                return Flow<Precision>(lhs.value_ * static_cast<Precision>(rhs));
            }

            friend Flow<Precision>
            operator*(const Flow<Precision>& lhs, const Gain<Precision>& rhs) {
                return Flow<Precision>(static_cast<Precision>(lhs) * rhs.value_);
            }

            friend Pressure<Precision>
            operator*(const Gain<Precision>& lhs, const Pressure<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ * static_cast<Precision>(rhs));
            }

            friend Pressure<Precision>
            operator*(const Pressure<Precision>& lhs, const Gain<Precision>& rhs) {
                return Pressure<Precision>(static_cast<Precision>(lhs) * rhs.value_);
            }

            friend Volume<Precision>
            operator*(const Gain<Precision>& lhs, const Volume<Precision>& rhs) {
                return Volume<Precision>(lhs.value_ * static_cast<Precision>(rhs));
            }

            friend Volume<Precision>
            operator*(const Volume<Precision>& lhs, const Gain<Precision>& rhs) {
                return Volume<Precision>(static_cast<Precision>(lhs) * rhs.value_);
            }
        private:
            Precision value_;
    };

    template <typename Precision, template <typename> typename Target>
    class Proportional {
        static_assert(is_airway_type<Target<Precision>>::value);
        public:
            Proportional(const Gain<Precision>& gain, const Target<Precision>& target)
                : gain_(gain)
                , target_(target)
            {}

            Flow<Precision>
            operator()(const Target<Precision>& current) {
                Precision value = static_cast<Precision>(gain_ * (target_ - current));
                return Flow(value);
            }

            void
            set_target(const Target<Precision>& target) { target_ = target; }
        private:
            Gain<Precision>     gain_;
            Target<Precision>   target_;
    };

    template <typename Precision, template <typename> typename Target>
    class Integral {
        static_assert(is_airway_type<Target<Precision>>::value);
        public:
            Integral(const Gain<Precision>& gain, const Target<Precision>& target)
                : gain_(gain)
                , target_(target)
                , errors_(100)
            {}

            Flow<Precision>
            operator()(const Target<Precision>& current) {
                errors_.push_back(target_ - current);
                Target<Precision> e = std::accumulate(errors_.begin(), errors_.end(), Target<Precision>());
                Precision value     = static_cast<Precision>(gain_ * e);
                return Flow(value);
            }

            void
            set_target(const Target<Precision>& target) {
                errors_.clear();
                target_ = target;
            }
        private:
            Gain<Precision>     gain_;
            Target<Precision>   target_;

            boost::circular_buffer<Target<Precision>> errors_;
    };
} // namespace control
} // namespace ventilation

#endif // VENTILATION_CONTROL_HPP__
