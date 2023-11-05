#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

#include "test-arbitrary.hpp"

using F32 = ventilation::Flow<float>;
using F64 = ventilation::Flow<double>;

using T32 = ventilation::Time<float>;
using T64 = ventilation::Time<double>;

using V32 = ventilation::Volume<float>;
using V64 = ventilation::Volume<double>;

TEST(Square, Zerof32) {
    V32 xs      = ventilation::integration::square(F32(1.0), T32(0.0));
    V32 ys      = ventilation::integration::square(F32(0.0), T32(1.0));

    EXPECT_EQ(xs, V32());
    EXPECT_EQ(ys, V32());
}

TEST(Square, Onef32) {
    V32 xs      = ventilation::integration::square(F32(1.0), T32(1.0));
    V32 ys      = ventilation::integration::square(F32(1.0), T32(1.0));

    EXPECT_EQ(xs, V32(1.0));
    EXPECT_EQ(ys, V32(1.0));
}

RC_GTEST_PROP(Square, Scalef32, (const F32& flow)) {
    float scale = *rc::gen::inRange(0, 100);

    T32 delta   = T32(1.0);
    V32 xs      = ventilation::integration::square(        flow, delta);
    V32 ys      = ventilation::integration::square(scale * flow, delta);
    RC_ASSERT(ys == scale * xs);
}

RC_GTEST_PROP(Squares, Gaussf32, (const F32& f, uint8_t count)) {
    T32 delta       = T32(1.0);
    std::vector<F32> fs(count, f);
    V32 expected    = V32(count * static_cast<float>(f));
    V32 actual      = ventilation::integration::squares(fs, delta);

    RC_ASSERT(expected == actual);
}

TEST(Square, Zerof64) {
    V64 xs      = ventilation::integration::square(F64(1.0), T64(0.0));
    V64 ys      = ventilation::integration::square(F64(0.0), T64(1.0));

    EXPECT_EQ(xs, V64());
    EXPECT_EQ(ys, V64());
}

TEST(Square, Onef64) {
    V64 xs      = ventilation::integration::square(F64(1.0), T64(1.0));
    V64 ys      = ventilation::integration::square(F64(1.0), T64(1.0));

    EXPECT_EQ(xs, V64(1.0));
    EXPECT_EQ(ys, V64(1.0));
}

RC_GTEST_PROP(Square, Scalef64, (const F64& flow)) {
    float scale = *rc::gen::inRange(0, 100);

    T64 delta   = T64(1.0);
    V64 xs      = ventilation::integration::square(        flow, delta);
    V64 ys      = ventilation::integration::square(scale * flow, delta);
    RC_ASSERT(ys == scale * xs);
}

RC_GTEST_PROP(Squares, Gaussf64, (const F64& f, uint8_t count)) {
    T64 delta       = T64(1.0);
    std::vector<F64> fs(count, f);
    V64 expected    = V64(count * static_cast<double>(f));
    V64 actual      = ventilation::integration::squares(fs, delta);

    RC_ASSERT(expected == actual);
}


int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
