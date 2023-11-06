#include <gtest/gtest.h>
#include <ventilation/ventilation.hpp>

namespace f32 {
using Control       = ventilation::modes::visitor::Control<float>;
using Cycle         = ventilation::cycle::Cycle<float>;
using Elastance     = ventilation::Elastance<float>;
using Flow          = ventilation::Flow<float>;
using Lung          = ventilation::lung::Forward<float>;
using Modes         = ventilation::Modes<float>;
using Packet        = ventilation::Packet<float>;
using Peak          = ventilation::pressure::Peak<float>;
using PEEP          = ventilation::PEEP<float>;
using Resistance    = ventilation::Resistance<float>;
using Tidal         = ventilation::volume::Tidal<float>;
using Time          = ventilation::Time<float>;
using PCV           = ventilation::modes::PCV<float>;
using VCV           = ventilation::modes::VCV<float>;

TEST(Visitor, PEEP) {
    Cycle   cycle(Time(1.0f), Time(0.5f), Time(3.0f), Time(0.5f));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5f), cycle);

    std::visit(ventilation::modes::setter::PEEP<float>{PEEP(6.0f)} , pcv);
    std::visit(ventilation::modes::setter::PEEP<float>{PEEP(6.0f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Peak) {
    Cycle   cycle(Time(1.0f), Time(0.5f), Time(3.0f), Time(0.5f));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5f), cycle);

    std::visit(ventilation::modes::setter::Peak<float>{Peak(6.0f)} , pcv);
    std::visit(ventilation::modes::setter::Peak<float>{Peak(6.0f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Tidal) {
    Cycle   cycle(Time(1.0f), Time(0.5f), Time(3.0f), Time(0.5f));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5f), cycle);

    std::visit(ventilation::modes::setter::Tidal<float>{Tidal(0.6f)} , pcv);
    std::visit(ventilation::modes::setter::Tidal<float>{Tidal(0.6f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Cycle) {
    Cycle   cycle(Time(1.0f), Time(0.5f), Time(3.0f), Time(0.5f));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5f), cycle);

    std::visit(ventilation::modes::setter::Cycle<float>{cycle} , pcv);
    std::visit(ventilation::modes::setter::Cycle<float>{cycle} , vcv);

    EXPECT_TRUE(true);
}
} // namespace f32

namespace f64 {
using Control       = ventilation::modes::visitor::Control<double>;
using Cycle         = ventilation::cycle::Cycle<double>;
using Elastance     = ventilation::Elastance<double>;
using Flow          = ventilation::Flow<double>;
using Lung          = ventilation::lung::Forward<double>;
using Modes         = ventilation::Modes<double>;
using Packet        = ventilation::Packet<double>;
using Peak          = ventilation::pressure::Peak<double>;
using PEEP          = ventilation::PEEP<double>;
using Resistance    = ventilation::Resistance<double>;
using Tidal         = ventilation::volume::Tidal<double>;
using Time          = ventilation::Time<double>;
using PCV           = ventilation::modes::PCV<double>;
using VCV           = ventilation::modes::VCV<double>;

TEST(Visitor, PEEP) {
    Cycle   cycle(Time(1.0f), Time(0.5), Time(3.0f), Time(0.5));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::PEEP<double>{PEEP(6.0f)} , pcv);
    std::visit(ventilation::modes::setter::PEEP<double>{PEEP(6.0f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Peak) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Peak<double>{Peak(6.0)} , pcv);
    std::visit(ventilation::modes::setter::Peak<double>{Peak(6.0)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Tidal) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Tidal<double>{Tidal(0.6f)} , pcv);
    std::visit(ventilation::modes::setter::Tidal<double>{Tidal(0.6f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Cycle) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Cycle<double>{cycle} , pcv);
    std::visit(ventilation::modes::setter::Cycle<double>{cycle} , vcv);

    EXPECT_TRUE(true);
}
} // namespace f64

namespace f128 {
using Control       = ventilation::modes::visitor::Control<long double>;
using Cycle         = ventilation::cycle::Cycle<long double>;
using Elastance     = ventilation::Elastance<long double>;
using Flow          = ventilation::Flow<long double>;
using Lung          = ventilation::lung::Forward<long double>;
using Modes         = ventilation::Modes<long double>;
using Packet        = ventilation::Packet<long double>;
using Peak          = ventilation::pressure::Peak<long double>;
using PEEP          = ventilation::PEEP<long double>;
using Resistance    = ventilation::Resistance<long double>;
using Tidal         = ventilation::volume::Tidal<long double>;
using Time          = ventilation::Time<long double>;
using PCV           = ventilation::modes::PCV<long double>;
using VCV           = ventilation::modes::VCV<long double>;

TEST(Visitor, PEEP) {
    Cycle   cycle(Time(1.0f), Time(0.5), Time(3.0f), Time(0.5));
    Modes pcv = PCV(PEEP(5.0f), Peak(20.0f), cycle);
    Modes vcv = VCV(PEEP(6.0f), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::PEEP<long double>{PEEP(6.0f)} , pcv);
    std::visit(ventilation::modes::setter::PEEP<long double>{PEEP(6.0f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Peak) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Peak<long double>{Peak(6.0)} , pcv);
    std::visit(ventilation::modes::setter::Peak<long double>{Peak(6.0)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Tidal) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Tidal<long double>{Tidal(0.6f)} , pcv);
    std::visit(ventilation::modes::setter::Tidal<long double>{Tidal(0.6f)} , vcv);

    EXPECT_TRUE(true);
}

TEST(Visitor, Cycle) {
    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes pcv = PCV(PEEP(5.0), Peak(20.0), cycle);
    Modes vcv = VCV(PEEP(6.0), Tidal(0.5), cycle);

    std::visit(ventilation::modes::setter::Cycle<long double>{cycle} , pcv);
    std::visit(ventilation::modes::setter::Cycle<long double>{cycle} , vcv);

    EXPECT_TRUE(true);
}
} // namespace f128

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
