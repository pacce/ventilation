#include <cstdint>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

TEST(VENTILATION_TYPE, POD) {
    ASSERT_FALSE(ventilation::is_ventilation_type<uint8_t>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<int8_t>::value);

    ASSERT_FALSE(ventilation::is_ventilation_type<uint16_t>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<int16_t>::value);

    ASSERT_FALSE(ventilation::is_ventilation_type<uint32_t>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<int32_t>::value);

    ASSERT_FALSE(ventilation::is_ventilation_type<uint64_t>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<int64_t>::value);

    ASSERT_FALSE(ventilation::is_ventilation_type<float>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<double>::value);
    ASSERT_FALSE(ventilation::is_ventilation_type<long double>::value);
}

TEST(VENTILATION_TYPE, FLOW) {
    using namespace ventilation;

    ASSERT_TRUE(is_flow_type<const Flow<float>>::value);
    ASSERT_TRUE(is_airway_type<const Flow<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Flow<float>>::value);

    ASSERT_FALSE(is_pressure_type<const Flow<float>>::value);
    ASSERT_FALSE(is_volume_type<const Flow<float>>::value);
    ASSERT_FALSE(is_lung_type<const Flow<float>>::value);

    ASSERT_TRUE(is_flow_type<const Flow<double>>::value);
    ASSERT_TRUE(is_airway_type<const Flow<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Flow<double>>::value);

    ASSERT_FALSE(is_pressure_type<const Flow<double>>::value);
    ASSERT_FALSE(is_volume_type<const Flow<double>>::value);
    ASSERT_FALSE(is_lung_type<const Flow<double>>::value);

    ASSERT_TRUE(is_flow_type<const Flow<long double>>::value);
    ASSERT_TRUE(is_airway_type<const Flow<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Flow<long double>>::value);

    ASSERT_FALSE(is_pressure_type<const Flow<long double>>::value);
    ASSERT_FALSE(is_volume_type<const Flow<long double>>::value);
    ASSERT_FALSE(is_lung_type<const Flow<long double>>::value);

    ASSERT_TRUE(is_flow_type<Flow<float>>::value);
    ASSERT_TRUE(is_airway_type<Flow<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Flow<float>>::value);

    ASSERT_FALSE(is_pressure_type<Flow<float>>::value);
    ASSERT_FALSE(is_volume_type<Flow<float>>::value);
    ASSERT_FALSE(is_lung_type<Flow<float>>::value);

    ASSERT_TRUE(is_flow_type<Flow<double>>::value);
    ASSERT_TRUE(is_airway_type<Flow<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Flow<double>>::value);

    ASSERT_FALSE(is_pressure_type<Flow<double>>::value);
    ASSERT_FALSE(is_volume_type<Flow<double>>::value);
    ASSERT_FALSE(is_lung_type<Flow<double>>::value);

    ASSERT_TRUE(is_flow_type<Flow<long double>>::value);
    ASSERT_TRUE(is_airway_type<Flow<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Flow<long double>>::value);

    ASSERT_FALSE(is_pressure_type<Flow<long double>>::value);
    ASSERT_FALSE(is_volume_type<Flow<long double>>::value);
    ASSERT_FALSE(is_lung_type<Flow<long double>>::value);
}

TEST(VENTILATION_TYPE, PRESSURE) {
    using namespace ventilation;

    ASSERT_TRUE(is_pressure_type<const Pressure<float>>::value);
    ASSERT_TRUE(is_airway_type<const Pressure<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Pressure<float>>::value);

    ASSERT_FALSE(is_flow_type<const Pressure<float>>::value);
    ASSERT_FALSE(is_volume_type<const Pressure<float>>::value);
    ASSERT_FALSE(is_lung_type<const Pressure<float>>::value);

    ASSERT_TRUE(is_pressure_type<const Pressure<double>>::value);
    ASSERT_TRUE(is_airway_type<const Pressure<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Pressure<double>>::value);

    ASSERT_FALSE(is_flow_type<const Pressure<double>>::value);
    ASSERT_FALSE(is_volume_type<const Pressure<double>>::value);
    ASSERT_FALSE(is_lung_type<const Pressure<double>>::value);

    ASSERT_TRUE(is_pressure_type<const Pressure<long double>>::value);
    ASSERT_TRUE(is_airway_type<const Pressure<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Pressure<long double>>::value);

    ASSERT_FALSE(is_flow_type<const Pressure<long double>>::value);
    ASSERT_FALSE(is_volume_type<const Pressure<long double>>::value);
    ASSERT_FALSE(is_lung_type<const Pressure<long double>>::value);

    ASSERT_TRUE(is_pressure_type<Pressure<float>>::value);
    ASSERT_TRUE(is_airway_type<Pressure<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Pressure<float>>::value);

    ASSERT_FALSE(is_flow_type<Pressure<float>>::value);
    ASSERT_FALSE(is_volume_type<Pressure<float>>::value);
    ASSERT_FALSE(is_lung_type<Pressure<float>>::value);

    ASSERT_TRUE(is_pressure_type<Pressure<double>>::value);
    ASSERT_TRUE(is_airway_type<Pressure<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Pressure<double>>::value);

    ASSERT_FALSE(is_flow_type<Pressure<double>>::value);
    ASSERT_FALSE(is_volume_type<Pressure<double>>::value);
    ASSERT_FALSE(is_lung_type<Pressure<double>>::value);

    ASSERT_TRUE(is_pressure_type<Pressure<long double>>::value);
    ASSERT_TRUE(is_airway_type<Pressure<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Pressure<long double>>::value);

    ASSERT_FALSE(is_flow_type<Pressure<long double>>::value);
    ASSERT_FALSE(is_volume_type<Pressure<long double>>::value);
    ASSERT_FALSE(is_lung_type<Pressure<long double>>::value);
}

TEST(VENTILATION_TYPE, VOLUME) {
    using namespace ventilation;

    ASSERT_TRUE(is_volume_type<const Volume<float>>::value);
    ASSERT_TRUE(is_airway_type<const Volume<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Volume<float>>::value);

    ASSERT_FALSE(is_flow_type<const Volume<float>>::value);
    ASSERT_FALSE(is_pressure_type<const Volume<float>>::value);
    ASSERT_FALSE(is_lung_type<const Volume<float>>::value);

    ASSERT_TRUE(is_volume_type<const Volume<double>>::value);
    ASSERT_TRUE(is_airway_type<const Volume<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Volume<double>>::value);

    ASSERT_FALSE(is_flow_type<const Volume<double>>::value);
    ASSERT_FALSE(is_pressure_type<const Volume<double>>::value);
    ASSERT_FALSE(is_lung_type<const Volume<double>>::value);

    ASSERT_TRUE(is_volume_type<const Volume<long double>>::value);
    ASSERT_TRUE(is_airway_type<const Volume<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Volume<long double>>::value);

    ASSERT_FALSE(is_flow_type<const Volume<long double>>::value);
    ASSERT_FALSE(is_pressure_type<const Volume<long double>>::value);
    ASSERT_FALSE(is_lung_type<const Volume<long double>>::value);

    ASSERT_TRUE(is_volume_type<Volume<float>>::value);
    ASSERT_TRUE(is_airway_type<Volume<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Volume<float>>::value);

    ASSERT_FALSE(is_flow_type<Volume<float>>::value);
    ASSERT_FALSE(is_pressure_type<Volume<float>>::value);
    ASSERT_FALSE(is_lung_type<Volume<float>>::value);

    ASSERT_TRUE(is_volume_type<Volume<double>>::value);
    ASSERT_TRUE(is_airway_type<Volume<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Volume<double>>::value);

    ASSERT_FALSE(is_flow_type<Volume<double>>::value);
    ASSERT_FALSE(is_pressure_type<Volume<double>>::value);
    ASSERT_FALSE(is_lung_type<Volume<double>>::value);

    ASSERT_TRUE(is_volume_type<Volume<long double>>::value);
    ASSERT_TRUE(is_airway_type<Volume<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Volume<long double>>::value);

    ASSERT_FALSE(is_flow_type<Volume<long double>>::value);
    ASSERT_FALSE(is_pressure_type<Volume<long double>>::value);
    ASSERT_FALSE(is_lung_type<Volume<long double>>::value);
}

TEST(VENTILATION_TYPE, ELASTANCE) {
    using namespace ventilation;

    ASSERT_TRUE(is_elastance_type<const Elastance<float>>::value);
    ASSERT_TRUE(is_lung_type<const Elastance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Elastance<float>>::value);

    ASSERT_FALSE(is_airway_type<const Elastance<float>>::value);
    ASSERT_FALSE(is_compliance_type<const Elastance<float>>::value);
    ASSERT_FALSE(is_resistance_type<const Elastance<float>>::value);

    ASSERT_TRUE(is_elastance_type<const Elastance<double>>::value);
    ASSERT_TRUE(is_lung_type<const Elastance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Elastance<double>>::value);

    ASSERT_FALSE(is_airway_type<const Elastance<double>>::value);
    ASSERT_FALSE(is_compliance_type<const Elastance<double>>::value);
    ASSERT_FALSE(is_resistance_type<const Elastance<double>>::value);

    ASSERT_TRUE(is_elastance_type<const Elastance<long double>>::value);
    ASSERT_TRUE(is_lung_type<const Elastance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Elastance<long double>>::value);

    ASSERT_FALSE(is_airway_type<const Elastance<long double>>::value);
    ASSERT_FALSE(is_compliance_type<const Elastance<long double>>::value);
    ASSERT_FALSE(is_resistance_type<const Elastance<long double>>::value);

    ASSERT_TRUE(is_elastance_type<Elastance<float>>::value);
    ASSERT_TRUE(is_lung_type<Elastance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Elastance<float>>::value);

    ASSERT_FALSE(is_airway_type<Elastance<float>>::value);
    ASSERT_FALSE(is_compliance_type<Elastance<float>>::value);
    ASSERT_FALSE(is_resistance_type<Elastance<float>>::value);

    ASSERT_TRUE(is_elastance_type<Elastance<double>>::value);
    ASSERT_TRUE(is_lung_type<Elastance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Elastance<double>>::value);

    ASSERT_FALSE(is_airway_type<Elastance<double>>::value);
    ASSERT_FALSE(is_compliance_type<Elastance<double>>::value);
    ASSERT_FALSE(is_resistance_type<Elastance<double>>::value);

    ASSERT_TRUE(is_elastance_type<Elastance<long double>>::value);
    ASSERT_TRUE(is_lung_type<Elastance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Elastance<long double>>::value);

    ASSERT_FALSE(is_airway_type<Elastance<long double>>::value);
    ASSERT_FALSE(is_compliance_type<Elastance<long double>>::value);
    ASSERT_FALSE(is_resistance_type<Elastance<long double>>::value);
}

TEST(VENTILATION_TYPE, COMPLIANCE) {
    using namespace ventilation;

    ASSERT_TRUE(is_compliance_type<const Compliance<float>>::value);
    ASSERT_TRUE(is_lung_type<const Compliance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Compliance<float>>::value);

    ASSERT_FALSE(is_airway_type<const Compliance<float>>::value);
    ASSERT_FALSE(is_elastance_type<const Compliance<float>>::value);
    ASSERT_FALSE(is_resistance_type<const Compliance<float>>::value);

    ASSERT_TRUE(is_compliance_type<const Compliance<double>>::value);
    ASSERT_TRUE(is_lung_type<const Compliance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Compliance<double>>::value);

    ASSERT_FALSE(is_airway_type<const Compliance<double>>::value);
    ASSERT_FALSE(is_elastance_type<const Compliance<double>>::value);
    ASSERT_FALSE(is_resistance_type<const Compliance<double>>::value);

    ASSERT_TRUE(is_compliance_type<const Compliance<long double>>::value);
    ASSERT_TRUE(is_lung_type<const Compliance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Compliance<long double>>::value);

    ASSERT_FALSE(is_airway_type<const Compliance<long double>>::value);
    ASSERT_FALSE(is_elastance_type<const Compliance<long double>>::value);
    ASSERT_FALSE(is_resistance_type<const Compliance<long double>>::value);

    ASSERT_TRUE(is_compliance_type<Compliance<float>>::value);
    ASSERT_TRUE(is_lung_type<Compliance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Compliance<float>>::value);

    ASSERT_FALSE(is_airway_type<Compliance<float>>::value);
    ASSERT_FALSE(is_elastance_type<Compliance<float>>::value);
    ASSERT_FALSE(is_resistance_type<Compliance<float>>::value);

    ASSERT_TRUE(is_compliance_type<Compliance<double>>::value);
    ASSERT_TRUE(is_lung_type<Compliance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Compliance<double>>::value);

    ASSERT_FALSE(is_airway_type<Compliance<double>>::value);
    ASSERT_FALSE(is_elastance_type<Compliance<double>>::value);
    ASSERT_FALSE(is_resistance_type<Compliance<double>>::value);

    ASSERT_TRUE(is_compliance_type<Compliance<long double>>::value);
    ASSERT_TRUE(is_lung_type<Compliance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Compliance<long double>>::value);

    ASSERT_FALSE(is_airway_type<Compliance<long double>>::value);
    ASSERT_FALSE(is_elastance_type<Compliance<long double>>::value);
    ASSERT_FALSE(is_resistance_type<Compliance<long double>>::value);
}

TEST(VENTILATION_TYPE, RESISTANCE) {
    using namespace ventilation;

    ASSERT_TRUE(is_resistance_type<const Resistance<float>>::value);
    ASSERT_TRUE(is_lung_type<const Resistance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<const Resistance<float>>::value);

    ASSERT_FALSE(is_airway_type<const Resistance<float>>::value);
    ASSERT_FALSE(is_elastance_type<const Resistance<float>>::value);
    ASSERT_FALSE(is_compliance_type<const Resistance<float>>::value);

    ASSERT_TRUE(is_resistance_type<const Resistance<double>>::value);
    ASSERT_TRUE(is_lung_type<const Resistance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Resistance<double>>::value);

    ASSERT_FALSE(is_airway_type<const Resistance<double>>::value);
    ASSERT_FALSE(is_elastance_type<const Resistance<double>>::value);
    ASSERT_FALSE(is_compliance_type<const Resistance<double>>::value);

    ASSERT_TRUE(is_resistance_type<const Resistance<long double>>::value);
    ASSERT_TRUE(is_lung_type<const Resistance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<const Resistance<long double>>::value);

    ASSERT_FALSE(is_airway_type<const Resistance<long double>>::value);
    ASSERT_FALSE(is_elastance_type<const Resistance<long double>>::value);
    ASSERT_FALSE(is_compliance_type<const Resistance<long double>>::value);

    ASSERT_TRUE(is_resistance_type<Resistance<float>>::value);
    ASSERT_TRUE(is_lung_type<Resistance<float>>::value);
    ASSERT_TRUE(is_ventilation_type<Resistance<float>>::value);

    ASSERT_FALSE(is_airway_type<Resistance<float>>::value);
    ASSERT_FALSE(is_elastance_type<Resistance<float>>::value);
    ASSERT_FALSE(is_compliance_type<Resistance<float>>::value);

    ASSERT_TRUE(is_resistance_type<Resistance<double>>::value);
    ASSERT_TRUE(is_lung_type<Resistance<double>>::value);
    ASSERT_TRUE(is_ventilation_type<Resistance<double>>::value);

    ASSERT_FALSE(is_airway_type<Resistance<double>>::value);
    ASSERT_FALSE(is_elastance_type<Resistance<double>>::value);
    ASSERT_FALSE(is_compliance_type<Resistance<double>>::value);

    ASSERT_TRUE(is_resistance_type<Resistance<long double>>::value);
    ASSERT_TRUE(is_lung_type<Resistance<long double>>::value);
    ASSERT_TRUE(is_ventilation_type<Resistance<long double>>::value);

    ASSERT_FALSE(is_airway_type<Resistance<long double>>::value);
    ASSERT_FALSE(is_elastance_type<Resistance<long double>>::value);
    ASSERT_FALSE(is_compliance_type<Resistance<long double>>::value);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
