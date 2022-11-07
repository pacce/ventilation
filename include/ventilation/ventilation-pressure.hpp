#ifndef VENTILATION_PRESSURE_HPP__
#define VENTILATION_PRESSURE_HPP__

#include <cmath>
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
                os << p.value_;
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

            friend std::partial_ordering
            operator<=>(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                if (std::isnan(lhs.value_) || std::isnan(rhs.value_)) {
                    return std::partial_ordering::unordered;
                }
                const double DBL_TOLERANCE = 0.01; // i.e. 0.10 == 0.109 (cmH2O)

                Precision difference = lhs.value_ - rhs.value_;
                if ((lhs.value_ == rhs.value_) || (std::abs(difference) <= DBL_TOLERANCE)) {
                    return std::partial_ordering::equivalent;
                } else if (difference > 0) {
                    return std::partial_ordering::greater;
                } else {
                    return std::partial_ordering::less;
                }
            }

            friend bool
            operator==(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) = default;

            friend bool
            operator!=(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) = default;
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_PRESSURE_HPP__
