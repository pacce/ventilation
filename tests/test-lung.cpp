#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using F32 = ventilation::Flow<float>;
using F64 = ventilation::Flow<double>;

using P32 = ventilation::Pressure<float>;
using P64 = ventilation::Pressure<double>;

using V32 = ventilation::Volume<float>;
using V64 = ventilation::Volume<double>;

using L32 = ventilation::Lung<float>;
using L64 = ventilation::Lung<double>;

RC_GTEST_PROP(Add, Scalef32, (const L32& lung, const V32& volume, const F32& flow)) {
    {
        P32 expected    = 2.0 * lung.forward(flow, V32(0.0));
        P32 actual      = lung.forward(2.0 * flow, V32(0.0));
        RC_ASSERT(expected == actual);
    }
    {
        P32 expected    = 2.0 * lung.forward(F32(0.0), volume);
        P32 actual      = lung.forward(F32(0.0), 2.0 * volume);
        RC_ASSERT(expected == actual);
    }
}

RC_GTEST_PROP(Add, Zerof32, (const L32& lung)) {
    RC_ASSERT(P32(0.0) == lung.forward(F32(0.0), V32(0.0)));
}

RC_GTEST_PROP(Add, Scalef64, (const L64& lung, const V64& volume, const F64& flow)) {
    {
        P64 expected    = 2.0 * lung.forward(flow, V64(0.0));
        P64 actual      = lung.forward(2.0 * flow, V64(0.0));
        RC_ASSERT(expected == actual);
    }
    {
        P64 expected    = 2.0 * lung.forward(F64(0.0), volume);
        P64 actual      = lung.forward(F64(0.0), 2.0 * volume);
        RC_ASSERT(expected == actual);
    }
}

RC_GTEST_PROP(Add, Zerof64, (const L64& lung)) {
    RC_ASSERT(P64(0.0) == lung.forward(F64(0.0), V64(0.0)));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
