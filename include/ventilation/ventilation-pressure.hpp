#ifndef VENTILATION_PRESSURE_HPP__
#define VENTILATION_PRESSURE_HPP__

#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Pressure {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Pressure() : Pressure(Precision()) {}
            explicit Pressure(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Pressure& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Pressure<Precision>&
            operator+=(const Pressure<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Pressure<Precision>&
            operator-=(const Pressure<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Pressure<Precision>&
            operator*=(const Pressure<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Pressure<Precision>
            operator+(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ + rhs.value_);
            }

            friend Pressure<Precision>
            operator-(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ - rhs.value_);
            }

            friend Pressure<Precision>
            operator*(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return Pressure<Precision>(lhs.value_ * rhs.value_);
            }

            friend Pressure<Precision>
            operator*(const Pressure<Precision>& lhs, const Precision& rhs) {
                return Pressure<Precision>(lhs.value_ * rhs);
            }

            friend Pressure<Precision>
            operator*(const Precision& lhs, const Pressure<Precision>& rhs) {
                return Pressure<Precision>(lhs * rhs.value_);
            }

            friend bool
            operator==(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_PRESSURE_HPP__
