#ifndef VENTILATION_VOLUME_HPP__
#define VENTILATION_VOLUME_HPP__

#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Volume {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            Volume() : Volume(Precision()) {}
            Volume(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Volume& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
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

            friend bool
            operator==(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                const double DBL_TOLERANCE = 0.1;
                return (lhs.value_ == rhs.value_)
                    || (std::abs(lhs.value_ - rhs.value_) <= DBL_TOLERANCE)
                    ;
            }

            friend bool
            operator!=(const Volume<Precision>& lhs, const Volume<Precision>& rhs) {
                return !(lhs == rhs);
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_VOLUME_HPP__
