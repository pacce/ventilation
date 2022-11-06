#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using R32 = ventilation::Resistance<float>;
using R64 = ventilation::Resistance<double>;

using F32 = ventilation::Flow<float>;
using F64 = ventilation::Flow<double>;

using P32 = ventilation::Pressure<float>;
using P64 = ventilation::Pressure<double>;

RC_GTEST_PROP(Add, Associativef32, (const R32& xs, const R32& ys, const R32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const R32& xs, const R32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const R32& xs)) {
    R32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const R32& xs)) {
    R32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const R32& xs, const R32& ys, const R32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const R32& xs, const R32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const R32& xs)) {
    R32 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const R32& xs)) {
    R32 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulVolume, Commutativef32, (const R32& xs, const F32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Neutralf32, (const R32& xs)) {
    F32 ys(1.0f);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Zerof32, (const R32& xs)) {
    F32 ys(0.0f);
    RC_ASSERT((xs * ys) == P32(0.0f));
}

// Tests double precision pressure implementation

RC_GTEST_PROP(Add, Associativef64, (const R64& xs, const R64& ys, const R64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const R64& xs, const R64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const R64& xs)) {
    R64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const R64& xs)) {
    R64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const R64& xs, const R64& ys, const R64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const R64& xs, const R64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const R64& xs)) {
    R64 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const R64& xs)) {
    R64 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Commutativef64, (const R64& xs)) {
    double ys = *rc::gen::inRange(-100, 100);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulScalar, Neutralf64, (const R64& xs)) {
    double ys = 1.0;
    RC_ASSERT((xs * ys) == R64(xs));
}

RC_GTEST_PROP(MulScalar, Zerof64, (const R64& xs)) {
    double ys = 0.0;
    RC_ASSERT((xs * ys) == R64(ys));
}

RC_GTEST_PROP(MulVolume, Commutativef64, (const R64& xs, const F64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Neutralf64, (const R64& xs)) {
    F64 ys(1.0);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulVolume, Zerof64, (const R64& xs)) {
    F64 ys(0.0);
    RC_ASSERT((xs * ys) == P64(0.0));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
