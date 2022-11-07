#ifndef VENTILATION_ELASTANCE_HPP__
#define VENTILATION_ELASTANCE_HPP__

#include <iomanip>
#include <ostream>

#include "ventilation-pressure.hpp"
#include "ventilation-volume.hpp"

namespace ventilation {
    template <typename Precision>
    class Elastance {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Elastance() : Elastance(Precision()) {}
            explicit Elastance(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Elastance& p) {
                os << p.value_;
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

            friend Elastance<Precision>
            operator*(const Elastance<Precision>& lhs, const Precision& rhs) {
                return Elastance<Precision>(lhs.value_ * rhs);
            }

            friend Elastance<Precision>
            operator*(const Precision& lhs, const Elastance<Precision>& rhs) {
                return Elastance<Precision>(lhs * rhs.value_);
            }

            friend Pressure<Precision>
            operator*(const Elastance<Precision>& lhs, const Volume<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ * static_cast<Precision>(rhs));
            }

            friend Pressure<Precision>
            operator*(const Volume<Precision>& lhs, const Elastance<Precision>& rhs) {
                return Pressure<Precision>(static_cast<Precision>(lhs) * rhs.value_);
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
