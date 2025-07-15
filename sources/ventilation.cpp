#include "ventilation/ventilation.hpp"
#include <iostream>

namespace ventilation {
namespace fixed {
    const float FORWARD             = 1e+6f;
    const float INVERSE             = 1e-6f;
    const std::int64_t PRECISION    = 1000;
} // namespace fixed
    Compliance::Compliance() : value_(0) {}
    Compliance::Compliance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("compliance value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Compliance::Compliance(std::int64_t v) : value_(v) {}

    Compliance::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Compliance& lhs, const Compliance& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys);
    }

    bool
    operator==(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Compliance& lhs, const Compliance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Compliance
    operator*(const Compliance& compliance, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Compliance((compliance.value_ * converted) / forward);
    }

    Compliance
    operator*(float scalar, const Compliance& compliance) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Compliance((compliance.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Compliance& compliance) {
        return os << std::format("{:.1f}L/cmH2O", static_cast<float>(compliance));
    }

    Elastance::Elastance() : value_(0) {}
    Elastance::Elastance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("elastance value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Elastance::Elastance(std::int64_t v) : value_(v) {}

    Elastance::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Elastance& lhs, const Elastance& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys);
    }

    bool
    operator==(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Elastance& lhs, const Elastance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Elastance
    operator*(const Elastance& elastance, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Elastance((elastance.value_ * converted) / forward);
    }

    Elastance
    operator*(float scalar, const Elastance& elastance) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Elastance((elastance.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Elastance& elastance) {
        return os << std::format("{:.1f}cmH2O/L", static_cast<float>(elastance));
    }

    Flow::Flow() : value_(0) {}
    Flow::Flow(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("flow value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Flow::Flow(std::int64_t v) : value_(v) {}

    Flow::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Flow& lhs, const Flow& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys);
    }

    bool
    operator==(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Flow& lhs, const Flow& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Flow
    operator+(const Flow& lhs, const Flow& rhs) {
        return Flow(lhs.value_ + rhs.value_);
    }

    Flow
    operator-(const Flow& lhs) {
        return Flow(-lhs.value_);
    }

    Flow
    operator-(const Flow& lhs, const Flow& rhs) {
        return Flow(lhs.value_ - rhs.value_);
    }

    Flow
    operator*(const Flow& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Flow((flow.value_ * converted) / forward);
    }

    Flow
    operator*(float scalar, const Flow& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Flow((flow.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Flow& flow) {
        return os << std::format("{:.1f}L/s", static_cast<float>(flow));
    }

    Pressure::Pressure() : value_(0) {}
    Pressure::Pressure(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("pressure value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Pressure::Pressure(std::int64_t v) : value_(v) {}

    Pressure::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Pressure& lhs, const Pressure& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys);
    }

    bool
    operator==(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Pressure& lhs, const Pressure& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Pressure
    operator+(const Pressure& lhs, const Pressure& rhs) {
        return Pressure(lhs.value_ + rhs.value_);
    }

    Pressure
    operator-(const Pressure& lhs) {
        return Pressure(-lhs.value_);
    }

    Pressure
    operator-(const Pressure& lhs, const Pressure& rhs) {
        return Pressure(lhs.value_ - rhs.value_);
    }

    Pressure
    operator*(const Pressure& pressure, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Pressure((pressure.value_ * converted) / forward);
    }

    Pressure
    operator*(float scalar, const Pressure& pressure) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Pressure((pressure.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Pressure& pressure) {
        return os << std::format("{:.1f}cmH2O", static_cast<float>(pressure));
    }

    Resistance::Resistance() : value_(0) {}
    Resistance::Resistance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("resistance value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Resistance::Resistance(std::int64_t v) : value_(v) {}

    Resistance::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Resistance& lhs, const Resistance& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys);
    }

    bool
    operator==(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Resistance& lhs, const Resistance& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Resistance
    operator*(const Resistance& resistance, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Resistance((resistance.value_ * converted) / forward);
    }

    Resistance
    operator*(float scalar, const Resistance& resistance) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Resistance((resistance.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Resistance& resistance) {
        return os << std::format("{:.1f}cmH2O.s/L", static_cast<float>(resistance));
    }

    Volume::Volume() : value_(0) {}
    Volume::Volume(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("volume value must be finite");
        } else {
            value_ = static_cast<std::int64_t>(v * fixed::FORWARD);
        }
    }

    Volume::Volume(std::int64_t v) : value_(v) {}

    Volume::operator
    float() const {
        return static_cast<float>(value_) * fixed::INVERSE;
    }

    std::strong_ordering
    operator<=>(const Volume& lhs, const Volume& rhs) {
        std::int64_t xs = lhs.value_ / fixed::PRECISION;
        std::int64_t ys = rhs.value_ / fixed::PRECISION;

        return (xs <=> ys); 
    }

    bool
    operator==(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }

    bool
    operator!=(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::equal;
    }

    bool
    operator<(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::less;
    }

    bool
    operator<=(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::greater;
    }

    bool
    operator>(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) == std::strong_ordering::greater;
    }

    bool
    operator>=(const Volume& lhs, const Volume& rhs) {
        return (lhs <=> rhs) != std::strong_ordering::less;
    }

    Volume
    operator+(const Volume& lhs, const Volume& rhs) {
        return Volume(lhs.value_ + rhs.value_);
    }

    Volume
    operator-(const Volume& lhs) {
        return Volume(-lhs.value_);
    }

    Volume
    operator-(const Volume& lhs, const Volume& rhs) {
        return Volume(lhs.value_ - rhs.value_);
    }

    Volume
    operator*(const Volume& volume, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Volume((volume.value_ * converted) / forward);
    }

    Volume
    operator*(float scalar, const Volume& volume) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        std::int64_t forward    = static_cast<std::int64_t>(fixed::FORWARD);
        std::int64_t converted  = static_cast<std::int64_t>(scalar * forward);

        return Volume((volume.value_ * converted) / forward);
    }

    std::ostream&
    operator<<(std::ostream& os, const Volume& volume) {
        return os << std::format("{:.1f}L", static_cast<float>(volume));
    }
} // namespace ventilation
