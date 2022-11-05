#ifndef VENTILATION_ELASTANCE_HPP__
#define VENTILATION_ELASTANCE_HPP__

#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Elastance {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Elastance(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Elastance& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Elastance<Precision>&
            operator+=(const Elastance<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Elastance<Precision>&
            operator-=(const Elastance<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Elastance<Precision>&
            operator*=(const Elastance<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Elastance<Precision>
            operator+(const Elastance<Precision>& lhs, const Elastance<Precision>& rhs) {
                return Elastance<Precision>(lhs.value_ + rhs.value_);
            }

            friend Elastance<Precision>
            operator-(const Elastance<Precision>& lhs, const Elastance<Precision>& rhs) {
                return Elastance<Precision>(lhs.value_ - rhs.value_);
            }

            friend Elastance<Precision>
            operator*(const Elastance<Precision>& lhs, const Elastance<Precision>& rhs) {
                return Elastance<Precision>(lhs.value_ * rhs.value_);
            }

            friend bool
            operator==(const Elastance<Precision>& lhs, const Elastance<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Elastance<Precision>& lhs, const Elastance<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_ELASTANCE_HPP__
