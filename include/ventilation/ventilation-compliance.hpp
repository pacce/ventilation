#ifndef VENTILATION_COMPLIANCE_HPP__
#define VENTILATION_COMPLIANCE_HPP__

#include <cmath>
#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Compliance {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Compliance(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Compliance& p) {
                os << p.value_;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Compliance<Precision>&
            operator+=(const Compliance<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Compliance<Precision>&
            operator-=(const Compliance<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Compliance<Precision>&
            operator*=(const Compliance<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Compliance<Precision>
            operator+(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return Compliance<Precision>(lhs.value_ + rhs.value_);
            }

            friend Compliance<Precision>
            operator-(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return Compliance<Precision>(lhs.value_ - rhs.value_);
            }

            friend Compliance<Precision>
            operator*(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return Compliance<Precision>(lhs.value_ * rhs.value_);
            }

            friend std::partial_ordering
            operator<=>(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                if (std::isnan(lhs.value_) || std::isnan(rhs.value_)) {
                    return std::partial_ordering::unordered;
                }
                const double DBL_TOLERANCE = 0.1;

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
            operator==(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::equivalent;
            }

            friend bool
            operator!=(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return (lhs <=> rhs) != std::partial_ordering::equivalent;
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_COMPLIANCE_HPP__
