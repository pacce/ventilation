#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using E32 = ventilation::Elastance<float>;
using E64 = ventilation::Elastance<double>;

using P32 = ventilation::Pressure<float>;
using P64 = ventilation::Pressure<double>;

using V32 = ventilation::Volume<float>;
using V64 = ventilation::Volume<double>;

RC_GTEST_PROP(Add, Associativef32, (const E32& xs, const E32& ys, const E32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const E32& xs, const E32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const E32& xs)) {
    E32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const E32& xs)) {
    E32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const E32& xs, const E32& ys, const E32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const E32& xs, const E32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const E32& xs)) {
    E32 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const E32& xs)) {
    E32 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Neutralf32, (const E32& xs)) {
    float ys = 1.0f;
    RC_ASSERT((xs * ys) == E32(xs));
}

RC_GTEST_PROP(MulScalar, Zerof32, (const E32& xs)) {
    float ys = 0.0f;
    RC_ASSERT((xs * ys) == E32(ys));
}

RC_GTEST_PROP(MulVolume, Commutativef32, (const E32& xs, const V32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Neutralf32, (const E32& xs)) {
    V32 ys(1.0f);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Zerof32, (const E32& xs)) {
    V32 ys(0.0f);
    RC_ASSERT((xs * ys) == P32(0.0f));
}

// Tests double precision pressure implementation

RC_GTEST_PROP(Add, Associativef64, (const E64& xs, const E64& ys, const E64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const E64& xs, const E64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const E64& xs)) {
    E64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const E64& xs)) {
    E64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const E64& xs, const E64& ys, const E64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const E64& xs, const E64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const E64& xs)) {
    E64 ys(1.0);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const E64& xs)) {
    E64 ys(0.0);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Neutralf64, (const E64& xs)) {
    double ys = 1.0;
    RC_ASSERT((xs * ys) == E64(xs));
}

RC_GTEST_PROP(MulScalar, Zerof64, (const E64& xs)) {
    double ys = 0.0;
    RC_ASSERT((xs * ys) == E64(ys));
}

RC_GTEST_PROP(MulVolume, Commutativef64, (const E64& xs, const V64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Neutralf64, (const E64& xs)) {
    V64 ys(1.0);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Zerof64, (const E64& xs)) {
    V64 ys(0.0);
    RC_ASSERT((xs * ys) == P64(0.0));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
