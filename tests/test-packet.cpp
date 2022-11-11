#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using P32 = ventilation::Packet<float>;
using P64 = ventilation::Packet<double>;

RC_GTEST_PROP(Add, Associativef32, (const P32& xs, const P32& ys, const P32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const P32& xs, const P32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const P32& xs)) {
    P32 ys{
          ventilation::Flow(0.0f)
        , ventilation::Pressure(0.0f)
        , ventilation::Volume(0.0f)
    };
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const P32& xs)) {
    P32 ys{
          ventilation::Flow(1.0f)
        , ventilation::Pressure(1.0f)
        , ventilation::Volume(1.0f)
    };
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const P32& xs, const P32& ys, const P32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const P32& xs, const P32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const P32& xs)) {
    P32 ys{
          ventilation::Flow(1.0f)
        , ventilation::Pressure(1.0f)
        , ventilation::Volume(1.0f)
    };
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const P32& xs)) {
    P32 ys{
          ventilation::Flow(0.0f)
        , ventilation::Pressure(0.0f)
        , ventilation::Volume(0.0f)
    };
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Commutativef32, (const P32& xs)) {
    float ys = *rc::gen::inRange(-100, 100);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulScalar, Neutralf32, (const P32& xs)) {
    float y = 1.0f;
    RC_ASSERT((xs * y) == xs);
}

RC_GTEST_PROP(MulScalar, Zerof32, (const P32& xs)) {
    float y = 0.0f;
    P32 ys{
          ventilation::Flow(y)
        , ventilation::Pressure(y)
        , ventilation::Volume(y)
    };
    RC_ASSERT((xs * y) == P32(ys));
}

// Tests double precision pressure implementation
RC_GTEST_PROP(Add, Associativef64, (const P64& xs, const P64& ys, const P64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const P64& xs, const P64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const P64& xs)) {
    P64 ys{
          ventilation::Flow(0.0)
        , ventilation::Pressure(0.0)
        , ventilation::Volume(0.0)
    };
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const P64& xs)) {
    P64 ys{
          ventilation::Flow(1.0)
        , ventilation::Pressure(1.0)
        , ventilation::Volume(1.0)
    };
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const P64& xs, const P64& ys, const P64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const P64& xs, const P64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const P64& xs)) {
    P64 ys{
          ventilation::Flow(1.0)
        , ventilation::Pressure(1.0)
        , ventilation::Volume(1.0)
    };
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const P64& xs)) {
    P64 ys{
          ventilation::Flow(0.0)
        , ventilation::Pressure(0.0)
        , ventilation::Volume(0.0)
    };
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Commutativef64, (const P64& xs)) {
    double ys = *rc::gen::inRange(-100, 100);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulScalar, Neutralf64, (const P64& xs)) {
    double y = 1.0;
    RC_ASSERT((xs * y) == xs);
}

RC_GTEST_PROP(MulScalar, Zerof64, (const P64& xs)) {
    double y = 0.0;
    P64 ys{
          ventilation::Flow(y)
        , ventilation::Pressure(y)
        , ventilation::Volume(y)
    };
    RC_ASSERT((xs * y) == P64(ys));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
