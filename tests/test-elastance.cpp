#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

using ventilation::Elastance;
using E32 = Elastance<float>;
using E64 = Elastance<double>;

namespace rc {
template<typename Precision>
struct Arbitrary<Elastance<Precision>> {
    static Gen<Elastance<Precision>>
    arbitrary() {
        return gen::construct<Elastance<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};
} // namespace rc

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
    E64 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const E64& xs)) {
    E64 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
