#ifndef TEST_ARBITRARY_HPP__
#define TEST_ARBITRARY_HPP__

#include <rapidcheck/gtest.h>
#include <ventilation/ventilation.hpp>

namespace rc {
template<typename Precision>
struct Arbitrary<ventilation::Compliance<Precision>> {
    static Gen<ventilation::Compliance<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Compliance<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Elastance<Precision>> {
    static Gen<ventilation::Elastance<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Elastance<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Flow<Precision>> {
    static Gen<ventilation::Flow<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Flow<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Pressure<Precision>> {
    static Gen<ventilation::Pressure<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Pressure<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Resistance<Precision>> {
    static Gen<ventilation::Resistance<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Resistance<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Volume<Precision>> {
    static Gen<ventilation::Volume<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Volume<Precision>>(
                gen::cast<Precision>(gen::inRange(-100, 100))
                );
    }
};

template<typename Precision>
struct Arbitrary<ventilation::Lung<Precision>> {
    static Gen<ventilation::Lung<Precision>>
    arbitrary() {
        return gen::construct<ventilation::Lung<Precision>>(
                  gen::arbitrary<ventilation::Resistance<Precision>>()
                , gen::arbitrary<ventilation::Elastance<Precision>>()
                );
    }
};
} // namespace rc

#endif // TEST_ARBITRARY_HPP__
