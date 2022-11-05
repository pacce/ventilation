#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

using ventilation::Pressure;
using P32 = Pressure<float>;
using P64 = Pressure<double>;

namespace rc {
template<typename Precision>
struct Arbitrary<Pressure<Precision>> {
    static Gen<Pressure<Precision>>
    arbitrary() {
        return gen::construct<Pressure<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};
} // namespace rc

RC_GTEST_PROP(Add, Associativef32, (const P32& xs, const P32& ys, const P32& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef32, (const P32& xs, const P32& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf32, (const P32& xs)) {
    P32 ys(0.0f);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf32, (const P32& xs)) {
    P32 ys(1.0f);
    RC_ASSERT((xs + ys) != xs);
}

RC_GTEST_PROP(Add, Associativef64, (const P64& xs, const P64& ys, const P64& zs)) {
    RC_ASSERT(((xs + ys) + zs) == (xs + ys + zs));
}

RC_GTEST_PROP(Add, Commutativef64, (const P64& xs, const P64& ys)) {
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(Add, Neutralf64, (const P64& xs)) {
    P64 ys(0.0);
    RC_ASSERT((xs + ys) == xs);
}

RC_GTEST_PROP(Add, Successorf64, (const P64& xs)) {
    P64 ys(1.0);
    RC_ASSERT((xs + ys) != xs);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
