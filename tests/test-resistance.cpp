#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using ventilation::Resistance;
using R32 = Resistance<float>;
using R64 = Resistance<double>;

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

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
