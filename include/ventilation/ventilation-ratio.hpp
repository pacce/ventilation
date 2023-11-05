#ifndef VENTILATION_RATIO_HPP__
#define VENTILATION_RATIO_HPP__

#include <cmath>
#include <ostream>
#include "ventilation-frequency.hpp"
#include "ventilation-time.hpp"

namespace ventilation {
namespace ratio {
    template <typename Precision>
    class Ratio {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            constexpr explicit Ratio(Precision i, Precision e) 
                : ratio_({i, e})
            {
                if (std::isnan(i)) { throw std::invalid_argument("inspiration ratio is NaN"); }
                if (std::isnan(e)) { throw std::invalid_argument("expiration ratio is NaN"); }

                if (!std::isfinite(i)) { throw std::invalid_argument("inspiration ratio is not finite"); }
                if (!std::isfinite(e)) { throw std::invalid_argument("expiration ratio is not finite"); }

                if (i <= 0.0)   { throw std::invalid_argument("inspiration ratio must be greater than zero"); }
                if (e <= 0.0)   { throw std::invalid_argument("inspiration ratio must be greater than zero"); }
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Ratio<Precision>& f) {
                os << f.ratio_.first << " : " << f.ratio_.second;
                return os;
            }

            Inspiration<Precision>
            inspiration(const Time<Precision>& period) const {
                Precision fraction = ratio_.first / this->total();
                return Inspiration<Precision>(period.count() * fraction);
            }

            Expiration<Precision>
            expiration(const Time<Precision>& period) const {
                Precision fraction = ratio_.second / this->total();
                return Expiration<Precision>(period.count() * fraction);
            }

            Inspiration<Precision>
            inspiration(const frequency::Frequency<Precision>& f) const {
                Precision fraction = ratio_.first / this->total();
                return Inspiration<Precision>(f.period().count() * fraction);
            }

            Expiration<Precision>
            expiration(const frequency::Frequency<Precision>& f) const {
                Precision fraction = ratio_.second / this->total();
                return Expiration<Precision>(f.period().count() * fraction);
            }

            std::pair<Inspiration<Precision>, Expiration<Precision>>
            operator()(const Time<Precision>& period) const {
                return std::make_pair(this->inspiration(period), this->expiration(period));
            }

            std::pair<Inspiration<Precision>, Expiration<Precision>>
            operator()(const frequency::Frequency<Precision>& f) const {
                return std::make_pair(this->inspiration(f), this->expiration(f));
            }
        private:
            Precision total() const { return ratio_.first + ratio_.second; }

            std::pair<Precision, Precision> ratio_;
    };
} // namespace ratio
} // namespace ventilation
#endif //  VENTILATION_RATIO_HPP__
