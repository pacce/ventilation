#include <gtest/gtest.h>
#include <limits>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

namespace rc {
    template <>
    struct Arbitrary<ventilation::Flow> {
        static Gen<ventilation::Flow>
        arbitrary() {
            const Gen<std::int32_t> value = gen::inRange(-1000, 1000);
            return gen::construct<ventilation::Flow>(
                    gen::map(value, [](std::int32_t v) { return static_cast<float>(v) * 1e-3f; })
            );
        }
    };
} // namespace rc

TEST(CONSTRUCTOR, ZERO) {
    EXPECT_EQ(static_cast<float>(ventilation::Flow()), 0.0f);
}

TEST(CONSTRUCTOR, EXCEPTION) {
    EXPECT_ANY_THROW(
            ventilation::Flow(std::numeric_limits<float>::quiet_NaN())
            );
    EXPECT_ANY_THROW(
            ventilation::Flow(std::numeric_limits<float>::infinity())
            );
}

TEST(COMPARISON, EQ) {
    EXPECT_EQ(ventilation::Flow(1.0f), ventilation::Flow(1.0f));
}

TEST(COMPARISON, NE) {
    EXPECT_NE(ventilation::Flow(1.0f), ventilation::Flow(2.0f));
}

TEST(COMPARISON, LT) {
    EXPECT_LT(ventilation::Flow(1.0f), ventilation::Flow(2.0f));
}

TEST(COMPARISON, LE) {
    EXPECT_LE(ventilation::Flow(1.0f), ventilation::Flow(1.0f));
    EXPECT_LE(ventilation::Flow(1.0f), ventilation::Flow(2.0f));
}

TEST(COMPARISON, GT) {
    EXPECT_GT(ventilation::Flow(2.0f), ventilation::Flow(1.0f));
}

TEST(COMPARISON, GE) {
    EXPECT_GE(ventilation::Flow(1.0f), ventilation::Flow(1.0f));
    EXPECT_GE(ventilation::Flow(2.0f), ventilation::Flow(1.0f));
}

RC_GTEST_PROP(
      ADDITION
    , NEUTRAL
    , (const ventilation::Flow& xs)
    ) 
{
    RC_ASSERT((xs + ventilation::Flow()) == xs); 
}

RC_GTEST_PROP(
      ADDITION
    , COMMUTATIVE
    , (const ventilation::Flow& xs, const ventilation::Flow& ys)
    ) 
{
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(
      ADDITION
    , ASSOCIATIVE
    , (const ventilation::Flow& xs, const ventilation::Flow& ys, const ventilation::Flow& zs)
    ) 
{
    RC_ASSERT((xs + ys) + zs == (xs + ys + zs));
}

RC_GTEST_PROP(
      SUBTRACTION
    , NEUTRAL
    , (const ventilation::Flow& xs)
    ) 
{
    RC_ASSERT((xs - ventilation::Flow()) == xs); 
}

RC_GTEST_PROP(
      SUBTRACTION
    , NEGATE
    , (const ventilation::Flow& xs)
    ) 
{
    RC_ASSERT((ventilation::Flow() - xs) == -xs); 
}

RC_GTEST_PROP(
      SUBTRACTION
    , ANTICOMMUTATIVE
    , (const ventilation::Flow& xs, const ventilation::Flow& ys)
    ) 
{
    RC_ASSERT((xs - ys) == -(ys - xs)); 
}

int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
