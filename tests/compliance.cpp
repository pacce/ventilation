#include <gtest/gtest.h>
#include <limits>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

namespace rc {
    template <>
    struct Arbitrary<ventilation::Compliance> {
        static Gen<ventilation::Compliance>
        arbitrary() {
            const Gen<std::int32_t> value = gen::inRange(-1000, 1000);
            return gen::construct<ventilation::Compliance>(
                    gen::map(value, [](std::int32_t v) { return static_cast<float>(v) * 1e-3f; })
            );
        }
    };
} // namespace rc

TEST(CONSTRUCTOR, ZERO) {
    EXPECT_EQ(static_cast<float>(ventilation::Compliance()), 0.0f);
}

TEST(CONSTRUCTOR, EXCEPTION) {
    EXPECT_ANY_THROW(
            ventilation::Compliance(std::numeric_limits<float>::quiet_NaN())
            );
    EXPECT_ANY_THROW(
            ventilation::Compliance(std::numeric_limits<float>::infinity())
            );
}

TEST(COMPARISON, EQ) {
    EXPECT_EQ(ventilation::Compliance(1.0f), ventilation::Compliance(1.0f));
}

TEST(COMPARISON, NE) {
    EXPECT_NE(ventilation::Compliance(1.0f), ventilation::Compliance(2.0f));
}

TEST(COMPARISON, LT) {
    EXPECT_LT(ventilation::Compliance(1.0f), ventilation::Compliance(2.0f));
}

TEST(COMPARISON, LE) {
    EXPECT_LE(ventilation::Compliance(1.0f), ventilation::Compliance(1.0f));
    EXPECT_LE(ventilation::Compliance(1.0f), ventilation::Compliance(2.0f));
}

TEST(COMPARISON, GT) {
    EXPECT_GT(ventilation::Compliance(2.0f), ventilation::Compliance(1.0f));
}

TEST(COMPARISON, GE) {
    EXPECT_GE(ventilation::Compliance(1.0f), ventilation::Compliance(1.0f));
    EXPECT_GE(ventilation::Compliance(2.0f), ventilation::Compliance(1.0f));
}

int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
