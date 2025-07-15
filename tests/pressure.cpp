#include <gtest/gtest.h>
#include <limits>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

namespace rc {
    template <>
    struct Arbitrary<ventilation::Pressure> {
        static Gen<ventilation::Pressure>
        arbitrary() {
            const Gen<std::int32_t> value = gen::inRange(-1000, 1000);
            return gen::construct<ventilation::Pressure>(
                    gen::map(value, [](std::int32_t v) { return static_cast<float>(v) * 1e-3f; })
            );
        }
    };
} // namespace rc

TEST(CONSTRUCTOR, ZERO) {
    EXPECT_EQ(static_cast<float>(ventilation::Pressure()), 0.0f);
}

TEST(CONSTRUCTOR, EXCEPTION) {
    EXPECT_ANY_THROW(
            ventilation::Pressure(std::numeric_limits<float>::quiet_NaN())
            );
    EXPECT_ANY_THROW(
            ventilation::Pressure(std::numeric_limits<float>::infinity())
            );
}

TEST(COMPARISON, EQ) {
    EXPECT_EQ(ventilation::Pressure(1.0f), ventilation::Pressure(1.0f));
}

TEST(COMPARISON, NE) {
    EXPECT_NE(ventilation::Pressure(1.0f), ventilation::Pressure(2.0f));
}

TEST(COMPARISON, LT) {
    EXPECT_LT(ventilation::Pressure(1.0f), ventilation::Pressure(2.0f));
}

TEST(COMPARISON, LE) {
    EXPECT_LE(ventilation::Pressure(1.0f), ventilation::Pressure(1.0f));
    EXPECT_LE(ventilation::Pressure(1.0f), ventilation::Pressure(2.0f));
}

TEST(COMPARISON, GT) {
    EXPECT_GT(ventilation::Pressure(2.0f), ventilation::Pressure(1.0f));
}

TEST(COMPARISON, GE) {
    EXPECT_GE(ventilation::Pressure(1.0f), ventilation::Pressure(1.0f));
    EXPECT_GE(ventilation::Pressure(2.0f), ventilation::Pressure(1.0f));
}

RC_GTEST_PROP(
      ADDITION
    , IDENTITY
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((xs + ventilation::Pressure()) == xs); 
}

RC_GTEST_PROP(
      ADDITION
    , COMMUTATIVE
    , (const ventilation::Pressure& xs, const ventilation::Pressure& ys)
    ) 
{
    RC_ASSERT((xs + ys) == (ys + xs));
}

RC_GTEST_PROP(
      ADDITION
    , ASSOCIATIVE
    , (const ventilation::Pressure& xs, const ventilation::Pressure& ys, const ventilation::Pressure& zs)
    ) 
{
    RC_ASSERT((xs + ys) + zs == (xs + ys + zs));
}

RC_GTEST_PROP(
      SUBTRACTION
    , NEUTRAL
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((xs - ventilation::Pressure()) == xs); 
}

RC_GTEST_PROP(
      SUBTRACTION
    , NEGATE
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((ventilation::Pressure() - xs) == -xs); 
}

RC_GTEST_PROP(
      SUBTRACTION
    , ANTICOMMUTATIVE
    , (const ventilation::Pressure& xs, const ventilation::Pressure& ys)
    ) 
{
    RC_ASSERT((xs - ys) == -(ys - xs)); 
}

RC_GTEST_PROP(
      MULTIPLICATION
    , IDENTITY
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((xs * 1.0f) == xs); 
    RC_ASSERT((1.0f * xs) == xs); 
}

RC_GTEST_PROP(
      MULTIPLICATION
    , DEFINITION
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((xs * 2.0f) == (xs + xs)); 
    RC_ASSERT((2.0f * xs) == (xs + xs)); 
}

RC_GTEST_PROP(
      MULTIPLICATION
    , ZERO
    , (const ventilation::Pressure& xs)
    ) 
{
    RC_ASSERT((xs * 0.0f) == ventilation::Pressure()); 
    RC_ASSERT((0.0f * xs) == ventilation::Pressure()); 
}

RC_GTEST_PROP(
      MULTIPLICATION
    , COMMUTATIVE
    , (const ventilation::Pressure& xs, float scalar)
    ) 
{
    RC_PRE(std::isfinite(scalar));
    RC_ASSERT((xs * scalar) == (scalar * xs));
}

TEST(MULTIPLICATION, EXCEPTION) {
    ventilation::Pressure flow;
    EXPECT_ANY_THROW(
            flow * std::numeric_limits<float>::quiet_NaN()
            );
    EXPECT_ANY_THROW(
            std::numeric_limits<float>::quiet_NaN() * flow
            );
    EXPECT_ANY_THROW(
            flow * std::numeric_limits<float>::infinity()
            );
    EXPECT_ANY_THROW(
            std::numeric_limits<float>::infinity() * flow
            );
}

int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
