#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using F32 = ventilation::Flow<float>;
using F64 = ventilation::Flow<double>;

RC_GTEST_PROP(Add, Associativef32, (const F32& xs, const F32& ys, const F32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const F32& xs, const F32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const F32& xs)) {
    F32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const F32& xs)) {
    F32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const F32& xs, const F32& ys, const F32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const F32& xs, const F32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const F32& xs)) {
    F32 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const F32& xs)) {
    F32 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Neutralf32, (const F32& xs)) {
    float ys = 1.0f;
    RC_ASSERT((xs * ys) == F32(xs));
}

RC_GTEST_PROP(MulScalar, Zerof32, (const F32& xs)) {
    float ys = 0.0f;
    RC_ASSERT((xs * ys) == F32(ys));
}

RC_GTEST_PROP(Comparison, Greaterf32, (const F32& xs)) {
    F32 ys(1.0f);
    RC_ASSERT((xs + ys) >  xs);
    RC_ASSERT((xs + ys) >= xs);
}

RC_GTEST_PROP(Comparison, Lesserf32, (const F32& xs)) {
    F32 ys(1.0f);
    RC_ASSERT(xs <  (xs + ys));
    RC_ASSERT(xs <= (xs + ys));
}

// Tests double precision pressure implementation
RC_GTEST_PROP(Add, Associativef64, (const F64& xs, const F64& ys, const F64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const F64& xs, const F64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const F64& xs)) {
    F64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const F64& xs)) {
    F64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const F64& xs, const F64& ys, const F64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const F64& xs, const F64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const F64& xs)) {
    F64 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const F64& xs)) {
    F64 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Neutralf64, (const F64& xs)) {
    double ys = 1.0;
    RC_ASSERT((xs * ys) == F64(xs));
}

RC_GTEST_PROP(MulScalar, Zerof64, (const F64& xs)) {
    double ys = 0.0;
    RC_ASSERT((xs * ys) == F64(ys));
}

RC_GTEST_PROP(Comparison, Greaterf64, (const F64& xs)) {
    F64 ys(1.0);
    RC_ASSERT((xs + ys) >  xs);
    RC_ASSERT((xs + ys) >= xs);
}

RC_GTEST_PROP(Comparison, Lesserf64, (const F64& xs)) {
    F64 ys(1.0);
    RC_ASSERT(xs <  (xs + ys));
    RC_ASSERT(xs <= (xs + ys));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
