#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

namespace f32 {
RC_GTEST_PROP(Elastance, Constant, (const ventilation::Elastance<float>& x, uint8_t size)) {
    using Elastance = ventilation::Elastance<float>;
    std::vector<Elastance> xs(size, x);
    Elastance expected = (size == 0) ? Elastance() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Flow, Constant, (const ventilation::Flow<float>& x, uint8_t size)) {
    using Flow = ventilation::Flow<float>;
    std::vector<Flow> xs(size, x);
    Flow expected = (size == 0) ? Flow() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Pressure, Constant, (const ventilation::Pressure<float>& x, uint8_t size)) {
    using Pressure = ventilation::Pressure<float>;
    std::vector<Pressure> xs(size, x);
    Pressure expected = (size == 0) ? Pressure() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Resistance, Constant, (const ventilation::Resistance<float>& x, uint8_t size)) {
    using Resistance = ventilation::Resistance<float>;
    std::vector<Resistance> xs(size, x);
    Resistance expected = (size == 0) ? Resistance() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}
}

namespace f64 {
RC_GTEST_PROP(Elastance, Constant, (const ventilation::Elastance<double>& x, uint8_t size)) {
    using Elastance = ventilation::Elastance<double>;
    std::vector<Elastance> xs(size, x);
    Elastance expected = (size == 0) ? Elastance() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Flow, Constant, (const ventilation::Flow<double>& x, uint8_t size)) {
    using Flow = ventilation::Flow<double>;
    std::vector<Flow> xs(size, x);
    Flow expected = (size == 0) ? Flow() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Pressure, Constant, (const ventilation::Pressure<double>& x, uint8_t size)) {
    using Pressure = ventilation::Pressure<double>;
    std::vector<Pressure> xs(size, x);
    Pressure expected = (size == 0) ? Pressure() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}

RC_GTEST_PROP(Resistance, Constant, (const ventilation::Resistance<double>& x, uint8_t size)) {
    using Resistance = ventilation::Resistance<double>;
    std::vector<Resistance> xs(size, x);
    Resistance expected = (size == 0) ? Resistance() : x;

    RC_ASSERT(ventilation::mean(xs) == expected);
}
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
