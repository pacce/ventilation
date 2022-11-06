#ifndef VENTILATION_RESISTANCE_HPP__
#define VENTILATION_RESISTANCE_HPP__

#include <iomanip>
#include <ostream>

#include "ventilation-flow.hpp"
#include "ventilation-pressure.hpp"

namespace ventilation {
    template <typename Precision>
    class Resistance {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Resistance() : Resistance(Precision()) {}
            explicit Resistance(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Resistance& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Resistance<Precision>&
            operator+=(const Resistance<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Resistance<Precision>&
            operator-=(const Resistance<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Resistance<Precision>&
            operator*=(const Resistance<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Resistance<Precision>
            operator+(const Resistance<Precision>& lhs, const Resistance<Precision>& rhs) {
                return Resistance<Precision>(lhs.value_ + rhs.value_);
            }

            friend Resistance<Precision>
            operator-(const Resistance<Precision>& lhs, const Resistance<Precision>& rhs) {
                return Resistance<Precision>(lhs.value_ - rhs.value_);
            }

            friend Resistance<Precision>
            operator*(const Resistance<Precision>& lhs, const Resistance<Precision>& rhs) {
                return Resistance<Precision>(lhs.value_ * rhs.value_);
            }

            friend Resistance<Precision>
            operator*(const Resistance<Precision>& lhs, const Precision& rhs) {
                return Resistance<Precision>(lhs.value_ * rhs);
            }

            friend Resistance<Precision>
            operator*(const Precision& lhs, const Resistance<Precision>& rhs) {
                return Resistance<Precision>(lhs * rhs.value_);
            }

            friend Pressure<Precision>
            operator*(const Resistance<Precision>& lhs, const Flow<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ * static_cast<Precision>(rhs));
            }

            friend Pressure<Precision>
            operator*(const Flow<Precision>& lhs, const Resistance<Precision>& rhs) {
                return Pressure<Precision>(static_cast<Precision>(lhs) * rhs.value_);
            }

            friend bool
            operator==(const Resistance<Precision>& lhs, const Resistance<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Resistance<Precision>& lhs, const Resistance<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_RESISTANCE_HPP__
