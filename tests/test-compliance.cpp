#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using ventilation::Compliance;
using C32 = Compliance<float>;
using C64 = Compliance<double>;


RC_GTEST_PROP(Add, Associativef32, (const C32& xs, const C32& ys, const C32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const C32& xs, const C32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const C32& xs)) {
    C32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const C32& xs)) {
    C32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const C32& xs, const C32& ys, const C32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const C32& xs, const C32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const C32& xs)) {
    C32 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const C32& xs)) {
    C32 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(Comparison, Greaterf32, (const C32& xs)) {
    C32 ys(1.0f);
    RC_ASSERT((xs + ys) > xs);
    RC_ASSERT((xs + ys) >= xs);
}

RC_GTEST_PROP(Comparison, Lesserf32, (const C32& xs)) {
    C32 ys(1.0f);
    RC_ASSERT(xs <  (xs + ys));
    RC_ASSERT(xs <= (xs + ys));
}

// Tests double precision pressure implementation
RC_GTEST_PROP(Add, Associativef64, (const C64& xs, const C64& ys, const C64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const C64& xs, const C64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const C64& xs)) {
    C64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const C64& xs)) {
    C64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const C64& xs, const C64& ys, const C64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const C64& xs, const C64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const C64& xs)) {
    C64 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const C64& xs)) {
    C64 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(Comparison, Greaterf64, (const C64& xs)) {
    C64 ys(1.0f);
    RC_ASSERT((xs + ys) > xs);
    RC_ASSERT((xs + ys) >= xs);
}

RC_GTEST_PROP(Comparison, Lesserf64, (const C64& xs)) {
    C64 ys(1.0f);
    RC_ASSERT(xs <  (xs + ys));
    RC_ASSERT(xs <= (xs + ys));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
