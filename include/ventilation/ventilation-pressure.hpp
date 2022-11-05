#ifndef VENTILATION_PRESSURE_HPP__
#define VENTILATION_PRESSURE_HPP__

#include <iomanip>
#include <ostream>

namespace ventilation {
    template <typename Precision>
    class Pressure {
        public:
            Pressure(Precision value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const Pressure& p) {
                os  << std::fixed
                    << std::setprecision(1)
                    << p.value_
                    ;
                return os;
            }
        private:
            Precision value_;
    };
} // namespace ventilation

#endif // VENTILATION_PRESSURE_HPP__
