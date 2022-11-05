#ifndef VENTILATION_FLOW_HPP__
#define VENTILATION_FLOW_HPP__

#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Flow {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Flow(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Flow& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Flow<Precision>&
            operator+=(const Flow<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Flow<Precision>&
            operator-=(const Flow<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Flow<Precision>&
            operator*=(const Flow<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Flow<Precision>
            operator+(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return Flow<Precision>(lhs.value_ + rhs.value_);
            }

            friend Flow<Precision>
            operator-(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return Flow<Precision>(lhs.value_ - rhs.value_);
            }

            friend Flow<Precision>
            operator*(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return Flow<Precision>(lhs.value_ * rhs.value_);
            }

            friend bool
            operator==(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_FLOW_HPP__
