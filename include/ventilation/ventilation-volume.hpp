#ifndef VENTILATION_VOLUME_HPP__
#define VENTILATION_VOLUME_HPP__

#include <cmath>
#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Volume {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            explicit Volume() : Volume(Precision()) {}
            explicit Volume(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Volume& p) {
                os << p.value_;
                return os;
            }

            explicit operator Precision() const noexcept {
                return value_;
            }

            Volume<Precision>&
            operator+=(const Volume<Precision>& rhs) {
                value_ += rhs.value_;
                return *this;
            }

            Volume<Precision>&
            operator-=(const Volume<Precision>& rhs) {
                value_ -= rhs.value_;
                return *this;
            }

            Volume<Precision>&
            operator*=(const Precision& rhs) {
                value_ *= rhs;
                return *this;
            }

            Volume<Precision>&
            operator*=(const Volume<Precision>& rhs) {
                value_ *= rhs.value_;
                return *this;
            }

            friend Volume<Precision>
            operator+(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return Volume<Precision>(lhs.value_ + rhs.value_);
            }

            friend Volume<Precision>
            operator-(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return Volume<Precision>(lhs.value_ - rhs.value_);
            }

            friend Volume<Precision>
            operator*(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return Volume<Precision>(lhs.value_ * rhs.value_);
            }

            friend Volume<Precision>
            operator*(const Volume<Precision>& lhs, const Precision& rhs) {
                return Volume<Precision>(lhs.value_ * rhs);
            }

            friend Volume<Precision>
            operator*(const Precision& lhs, const Volume<Precision>& rhs) {
                return Volume<Precision>(lhs * rhs.value_);
            }

            friend std::partial_ordering
            operator<=>(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                if (std::isnan(lhs.value_) || std::isnan(rhs.value_)) {
                    return std::partial_ordering::unordered;
                }
                const double DBL_TOLERANCE = 1e-4;

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
            operator==(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return (lhs <=> rhs) == std::partial_ordering::equivalent;
            }

            friend bool
            operator!=(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return (lhs <=> rhs) != std::partial_ordering::equivalent;
            }
        protected:
            Precision value_;
    };
namespace volume {
    template <typename Precision>
    class Tidal : public Volume<Precision> {
        public:
            explicit Tidal() : Tidal(Precision()) {}
            explicit Tidal(Precision value) : Volume<Precision>(value) {}
            explicit Tidal(const Volume<Precision>& p) : Volume<Precision>(p) {}
    };
} // namespace volume
} // namespace ventilation

#endif // VENTILATION_VOLUME_HPP__
