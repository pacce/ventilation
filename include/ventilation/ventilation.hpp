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
    class Resistance;
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
            operator*(const Compliance& compliance, float scalar);

            friend Compliance
            operator*(float scalar, const Compliance& compliance);

            friend std::ostream&
            operator<<(std::ostream& os, const Compliance& compliance);
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
            operator*(const Elastance& elastance, float scalar);

            friend Elastance
            operator*(float scalar, const Elastance& elastance);

            friend std::ostream&
            operator<<(std::ostream& os, const Elastance& elastance);
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
            operator*(const Pressure& pressure, float scalar);

            friend Pressure
            operator*(float scalar, const Pressure& pressure);

            friend std::ostream&
            operator<<(std::ostream& os, const Pressure& pressure);
        private:
            Pressure(std::int32_t v);

            std::int32_t value_;
    };

    class Resistance {
        public:
            Resistance();
            explicit Resistance(float v);
            explicit operator float() const;

            friend bool
            operator==(const Resistance& lhs, const Resistance& rhs);

            friend bool
            operator!=(const Resistance& lhs, const Resistance& rhs);

            friend bool
            operator<(const Resistance& lhs, const Resistance& rhs);

            friend bool
            operator<=(const Resistance& lhs, const Resistance& rhs);

            friend bool
            operator>(const Resistance& lhs, const Resistance& rhs);

            friend bool
            operator>=(const Resistance& lhs, const Resistance& rhs);

            friend Resistance
            operator*(const Resistance& resistance, float scalar);

            friend Resistance
            operator*(float scalar, const Resistance& resistance);

            friend std::ostream&
            operator<<(std::ostream& os, const Resistance& resistance);
        private:
            Resistance(std::int32_t v);

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
            operator*(const Volume& volume, float scalar);

            friend Volume
            operator*(float scalar, const Volume& volume);

            friend std::ostream&
            operator<<(std::ostream& os, const Volume& volume);
        private:
            Volume(std::int32_t v);

            std::int32_t value_;
    };
} // namespace ventilation

#endif // VENTILATION_HPP__
