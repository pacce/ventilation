#ifndef VENTILATION_COMPLIANCE_HPP__
#define VENTILATION_COMPLIANCE_HPP__

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

            friend bool
            operator==(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Compliance<Precision>& lhs, const Compliance<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_COMPLIANCE_HPP__
