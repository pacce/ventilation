#include "ventilation/ventilation.hpp"

namespace ventilation {
    Compliance::Compliance() : value_(0) {}
    Compliance::Compliance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("compliance value must be finite");
        } else {
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Compliance::Compliance(std::int32_t v) : value_(v) {}

    Compliance::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Compliance& lhs, const Compliance& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
    operator*(const Compliance& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Compliance(static_cast<float>(flow) * scalar);
    }

    Compliance
    operator*(float scalar, const Compliance& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Compliance(static_cast<float>(flow) * scalar);
    }

    std::ostream&
    operator<<(std::ostream& os, const Compliance& flow) {
        return os << std::format("{:.1f}L/cmH2O", static_cast<float>(flow));
    }

    Elastance::Elastance() : value_(0) {}
    Elastance::Elastance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("elastance value must be finite");
        } else {
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Elastance::Elastance(std::int32_t v) : value_(v) {}

    Elastance::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Elastance& lhs, const Elastance& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
    operator*(const Elastance& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Elastance(static_cast<float>(flow) * scalar);
    }

    Elastance
    operator*(float scalar, const Elastance& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Elastance(static_cast<float>(flow) * scalar);
    }

    std::ostream&
    operator<<(std::ostream& os, const Elastance& flow) {
        return os << std::format("{:.1f}cmH2O/L", static_cast<float>(flow));
    }

    Flow::Flow() : value_(0) {}
    Flow::Flow(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("flow value must be finite");
        } else {
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Flow::Flow(std::int32_t v) : value_(v) {}

    Flow::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Flow& lhs, const Flow& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
        return Flow(static_cast<float>(flow) * scalar);
    }

    Flow
    operator*(float scalar, const Flow& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Flow(static_cast<float>(flow) * scalar);
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
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Pressure::Pressure(std::int32_t v) : value_(v) {}

    Pressure::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Pressure& lhs, const Pressure& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
    operator*(const Pressure& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Pressure(static_cast<float>(flow) * scalar);
    }

    Pressure
    operator*(float scalar, const Pressure& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Pressure(static_cast<float>(flow) * scalar);
    }

    std::ostream&
    operator<<(std::ostream& os, const Pressure& flow) {
        return os << std::format("{:.1f}cmH2O", static_cast<float>(flow));
    }

    Resistance::Resistance() : value_(0) {}
    Resistance::Resistance(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("resistance value must be finite");
        } else {
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Resistance::Resistance(std::int32_t v) : value_(v) {}

    Resistance::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Resistance& lhs, const Resistance& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
    operator*(const Resistance& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Resistance(static_cast<float>(flow) * scalar);
    }

    Resistance
    operator*(float scalar, const Resistance& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Resistance(static_cast<float>(flow) * scalar);
    }

    std::ostream&
    operator<<(std::ostream& os, const Resistance& flow) {
        return os << std::format("{:.1f}cmH2O.s/L", static_cast<float>(flow));
    }

    Volume::Volume() : value_(0) {}
    Volume::Volume(float v) {
        if (not std::isfinite(v)) {
            throw std::domain_error("volume value must be finite");
        } else {
            value_ = static_cast<std::int32_t>(v * 1e+3f);
        }
    }

    Volume::Volume(std::int32_t v) : value_(v) {}

    Volume::operator
    float() const {
        return static_cast<float>(value_) * 1e-3f;
    }

    std::strong_ordering
    operator<=>(const Volume& lhs, const Volume& rhs) {
        float xs = static_cast<float>(lhs);
        float ys = static_cast<float>(rhs);

        if (xs == ys) {
            return std::strong_ordering::equal;
        } else if (xs < ys) {
            return std::strong_ordering::less;
        } else {
            return std::strong_ordering::greater;
        }
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
    operator*(const Volume& flow, float scalar) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Volume(static_cast<float>(flow) * scalar);
    }

    Volume
    operator*(float scalar, const Volume& flow) {
        if (not std::isfinite(scalar)) { throw std::domain_error("scalar value must be finite"); }
        return Volume(static_cast<float>(flow) * scalar);
    }

    std::ostream&
    operator<<(std::ostream& os, const Volume& flow) {
        return os << std::format("{:.1f}L", static_cast<float>(flow));
    }
} // namespace ventilation
