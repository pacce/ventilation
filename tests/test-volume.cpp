#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

using ventilation::Volume;
using V32 = Volume<float>;
using V64 = Volume<double>;

namespace rc {
template<typename Precision>
struct Arbitrary<Volume<Precision>> {
    static Gen<Volume<Precision>>
    arbitrary() {
        return gen::construct<Volume<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};
} // namespace rc

RC_GTEST_PROP(Add, Associativef32, (const V32& xs, const V32& ys, const V32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const V32& xs, const V32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const V32& xs)) {
    V32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const V32& xs)) {
    V32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef32, (const V32& xs, const V32& ys, const V32& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef32, (const V32& xs, const V32& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf32, (const V32& xs)) {
    V32 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof32, (const V32& xs)) {
    V32 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Commutativef32, (const V32& xs)) {
    float ys = *rc::gen::inRange(-100, 100);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulScalar, Neutralf32, (const V32& xs)) {
    float ys = 1.0f;
    RC_ASSERT((xs * ys) == V32(xs));
}

RC_GTEST_PROP(MulScalar, Zerof32, (const V32& xs)) {
    float ys = 0.0f;
    RC_ASSERT((xs * ys) == V32(ys));
}

// Tests double precision pressure implementation

RC_GTEST_PROP(Add, Associativef64, (const V64& xs, const V64& ys, const V64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const V64& xs, const V64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const V64& xs)) {
    V64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const V64& xs)) {
    V64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Mul, Associativef64, (const V64& xs, const V64& ys, const V64& zs)) {
    RC_ASSERT(((xs * ys) * zs) == (xs * ys * zs));
}

RC_GTEST_PROP(Mul, Commutativef64, (const V64& xs, const V64& ys)) {
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(Mul, Neutralf64, (const V64& xs)) {
    V64 ys(1.0f);
    RC_ASSERT((xs * ys) == xs);
}

RC_GTEST_PROP(Mul, Zerof64, (const V64& xs)) {
    V64 ys(0.0f);
    RC_ASSERT((xs * ys) == ys);
}

RC_GTEST_PROP(MulScalar, Commutativef64, (const V64& xs)) {
    double ys = *rc::gen::inRange(-100, 100);
    RC_ASSERT((xs * ys) == (ys * xs));
}

RC_GTEST_PROP(MulScalar, Neutralf64, (const V64& xs)) {
    double ys = 1.0;
    RC_ASSERT((xs * ys) == V64(xs));
}

RC_GTEST_PROP(MulScalar, Zerof64, (const V64& xs)) {
    double ys = 0.0;
    RC_ASSERT((xs * ys) == V64(ys));
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
