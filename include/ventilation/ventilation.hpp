#ifndef VENTILATION_HPP__
#define VENTILATION_HPP__

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <format>

namespace ventilation {
    // Forward declaration
    class Compliance;
    class Elastance;
    class Flow;
    class Pressure;
    class Volume;

    class Compliance {
        public:
            Compliance();
            explicit Compliance(float v);
            explicit operator float() const;

            friend bool
            operator==(const Compliance& lhs, const Compliance& rhs);

            friend bool
            operator!=(const Compliance& lhs, const Compliance& rhs);

            friend bool
            operator<(const Compliance& lhs, const Compliance& rhs);

            friend bool
            operator<=(const Compliance& lhs, const Compliance& rhs);

            friend bool
            operator>(const Compliance& lhs, const Compliance& rhs);

            friend bool
            operator>=(const Compliance& lhs, const Compliance& rhs);

            friend Compliance
            operator*(const Compliance& flow, float scalar);

            friend Compliance
            operator*(float scalar, const Compliance& flow);

            friend std::ostream&
            operator<<(std::ostream& os, const Compliance& flow);
        private:
            Compliance(std::int32_t v);

            std::int32_t value_;
    };

    class Elastance {
        public:
            Elastance();
            explicit Elastance(float v);
            explicit operator float() const;

            friend bool
            operator==(const Elastance& lhs, const Elastance& rhs);

            friend bool
            operator!=(const Elastance& lhs, const Elastance& rhs);

            friend bool
            operator<(const Elastance& lhs, const Elastance& rhs);

            friend bool
            operator<=(const Elastance& lhs, const Elastance& rhs);

            friend bool
            operator>(const Elastance& lhs, const Elastance& rhs);

            friend bool
            operator>=(const Elastance& lhs, const Elastance& rhs);

            friend Elastance
            operator*(const Elastance& flow, float scalar);

            friend Elastance
            operator*(float scalar, const Elastance& flow);

            friend std::ostream&
            operator<<(std::ostream& os, const Elastance& flow);
        private:
            Elastance(std::int32_t v);

            std::int32_t value_;
    };

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

            friend Flow
            operator-(const Flow& lhs);

            friend Flow
            operator-(const Flow& lhs, const Flow& rhs);

            friend Flow
            operator*(const Flow& flow, float scalar);

            friend Flow
            operator*(float scalar, const Flow& flow);

            friend std::ostream&
            operator<<(std::ostream& os, const Flow& flow);
        private:
            Flow(std::int32_t v);

            std::int32_t value_;
    };

    class Pressure {
        public:
            Pressure();
            explicit Pressure(float v);
            explicit operator float() const;

            friend bool
            operator==(const Pressure& lhs, const Pressure& rhs);

            friend bool
            operator!=(const Pressure& lhs, const Pressure& rhs);

            friend bool
            operator<(const Pressure& lhs, const Pressure& rhs);

            friend bool
            operator<=(const Pressure& lhs, const Pressure& rhs);

            friend bool
            operator>(const Pressure& lhs, const Pressure& rhs);

            friend bool
            operator>=(const Pressure& lhs, const Pressure& rhs);

            friend Pressure
            operator+(const Pressure& lhs, const Pressure& rhs);

            friend Pressure
            operator-(const Pressure& lhs);

            friend Pressure
            operator-(const Pressure& lhs, const Pressure& rhs);

            friend Pressure
            operator*(const Pressure& flow, float scalar);

            friend Pressure
            operator*(float scalar, const Pressure& flow);

            friend std::ostream&
            operator<<(std::ostream& os, const Pressure& flow);
        private:
            Pressure(std::int32_t v);

            std::int32_t value_;
    };

    class Volume {
        public:
            Volume();
            explicit Volume(float v);
            explicit operator float() const;

            friend bool
            operator==(const Volume& lhs, const Volume& rhs);

            friend bool
            operator!=(const Volume& lhs, const Volume& rhs);

            friend bool
            operator<(const Volume& lhs, const Volume& rhs);

            friend bool
            operator<=(const Volume& lhs, const Volume& rhs);

            friend bool
            operator>(const Volume& lhs, const Volume& rhs);

            friend bool
            operator>=(const Volume& lhs, const Volume& rhs);

            friend Volume
            operator+(const Volume& lhs, const Volume& rhs);

            friend Volume
            operator-(const Volume& lhs);

            friend Volume
            operator-(const Volume& lhs, const Volume& rhs);

            friend Volume
            operator*(const Volume& flow, float scalar);

            friend Volume
            operator*(float scalar, const Volume& flow);

            friend std::ostream&
            operator<<(std::ostream& os, const Volume& flow);
        private:
            Volume(std::int32_t v);

            std::int32_t value_;
    };
} // namespace ventilation

#endif // VENTILATION_HPP__
