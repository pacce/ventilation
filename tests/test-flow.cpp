#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

using ventilation::Flow;
using F32 = Flow<float>;
using F64 = Flow<double>;

namespace rc {
template<typename Precision>
struct Arbitrary<Flow<Precision>> {
    static Gen<Flow<Precision>>
    arbitrary() {
        return gen::construct<Flow<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};
} // namespace rc

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

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}