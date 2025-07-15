#ifndef VENTILATION_HPP__
#define VENTILATION_HPP__

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <format>

namespace ventilation {
    class Flow {
        public:
            Flow();
            explicit Flow(float v);
            explicit operator float() const;

            friend bool
            operator==(const Flow& lhs, const Flow& rhs);

            friend bool
            operator!=(const Flow& lhs, const Flow& rhs);

            friend bool
            operator<(const Flow& lhs, const Flow& rhs);

            friend bool
            operator<=(const Flow& lhs, const Flow& rhs);

            friend bool
            operator>(const Flow& lhs, const Flow& rhs);

            friend bool
            operator>=(const Flow& lhs, const Flow& rhs);

            friend Flow
            operator+(const Flow& lhs, const Flow& rhs);

            friend std::ostream&
            operator<<(std::ostream& os, const Flow& flow);
        private:
            Flow(std::int32_t v);

            std::int32_t value_;
    };
} // namespace ventilation

#endif // VENTILATION_HPP__
