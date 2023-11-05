#ifndef VENTILATION_FREQUENCY_HPP__
#define VENTILATION_FREQUENCY_HPP__

#include <ostream>
#include "ventilation-time.hpp"

namespace ventilation {
namespace frequency {
    template <typename Precision>
    class Frequency {
        static_assert(std::is_floating_point<Precision>::value);
        public:
            constexpr explicit Frequency(Precision value) : value_(value) {}
            explicit operator Precision() const noexcept {
                return value_;
            }

            template<typename U>
            explicit operator Frequency<U>() const noexcept {
                return Frequency<U>(static_cast<U>(value_));
            }

            Time<Precision>
            period() const {
                return Time<Precision>(1.0 / value_);
            }

            friend std::ostream&
            operator<<(std::ostream& os, const Frequency<Precision>& f) {
                os << f.value_;
                return os;
            }
        private:
            Precision value_;
    };
namespace literals {
    constexpr ventilation::frequency::Frequency<double>
    operator""_hz(long double value) {
        return ventilation::frequency::Frequency(static_cast<double>(value));
    }

    constexpr ventilation::frequency::Frequency<double>
    operator""_hz(unsigned long long value) {
        return ventilation::frequency::Frequency(static_cast<double>(value));
    }

    constexpr ventilation::frequency::Frequency<double>
    operator""_bpm(long double value) {
        return ventilation::frequency::Frequency(static_cast<double>(value / 60.0));
    }

    constexpr ventilation::frequency::Frequency<double>
    operator""_bpm(unsigned long long value) {
        return ventilation::frequency::Frequency(static_cast<double>(value / 60.0));
    }
} // namespace literals
} // namespace frequency
} // namespace ventilation

#endif //  VENTILATION_FREQUENCY_HPP__
