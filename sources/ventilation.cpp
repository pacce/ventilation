#include "ventilation/ventilation.hpp"

namespace ventilation {
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
} // namespace ventilation
