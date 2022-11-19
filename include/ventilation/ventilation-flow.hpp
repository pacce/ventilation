#ifndef VENTILATION_FLOW_HPP__
#define VENTILATION_FLOW_HPP__

#include <cmath>
#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Flow {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Flow() : Flow(Precision()) {}
            explicit Flow(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Flow& p) {
                os << p.value_;
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

            friend Flow<Precision>
            operator*(const Flow<Precision>& lhs, const Precision& rhs) {
                return Flow<Precision>(lhs.value_ * rhs);
            }

            friend Flow<Precision>
            operator*(const Precision& lhs, const Flow<Precision>& rhs) {
                return Flow<Precision>(lhs * rhs.value_);
            }

            friend std::partial_ordering
            operator<=>(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                if (std::isnan(lhs.value_) || std::isnan(rhs.value_)) {
                    return std::partial_ordering::unordered;
                }
                const double DBL_TOLERANCE = 1e-3;

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
            operator==(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::equivalent;
            }

            friend bool
            operator!=(const Flow<Precision>& lhs, const Flow<Precision>& rhs) {
                return (lhs <=> rhs) != std::partial_ordering::equivalent;
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_FLOW_HPP__
