#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

using ventilation::Resistance;
using R32 = Resistance<float>;
using R64 = Resistance<double>;

namespace rc {
template<typename Precision>
struct Arbitrary<Resistance<Precision>> {
    static Gen<Resistance<Precision>>
    arbitrary() {
        return gen::construct<Resistance<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};
} // namespace rc

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

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
