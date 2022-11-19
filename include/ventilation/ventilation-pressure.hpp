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
            operator==(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::equivalent;
            }

            friend bool
            operator!=(const Pressure<Precision>& lhs, const Pressure<Precision>& rhs) {
                return (lhs <=> rhs) != std::partial_ordering::equivalent;
            }
        private:
            Precision value_;
    };

    template <typename Precision>
    class PEEP : public Pressure<Precision> {
        public:
            explicit PEEP() : PEEP(Precision()) {}
            explicit PEEP(Precision value) : Pressure<Precision>(value) {}
            explicit PEEP(const Pressure<Precision>& p) : Pressure<Precision>(p) {}
    };
namespace pressure {
    template <typename Precision>
    class Peak : public Pressure<Precision> {
        public:
            explicit Peak() : Peak(Precision()) {}
            explicit Peak(Precision value) : Pressure<Precision>(value) {}
            explicit Peak(const Pressure<Precision>& p) : Pressure<Precision>(p) {}
    };

    template <typename Precision>
    class Delta : public Pressure<Precision> {
        public:
            explicit Delta() : Delta(Precision()) {}
            explicit Delta(Precision value) : Pressure<Precision>(value) {}
            explicit Delta(const Pressure<Precision>& p) : Pressure<Precision>(p) {}
    };
} // namespace pressure
} // namespace ventilation

#endif // VENTILATION_PRESSURE_HPP__
