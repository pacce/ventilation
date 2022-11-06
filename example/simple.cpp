#include <chrono>
#include <iostream>
#include <ventilation/ventilation.hpp>

int
main(int argc, char** argv) {
    ventilation::Elastance<float>   elastance(1000.0 / 10.0);
    ventilation::Resistance<float>  resistance(30.0);
    ventilation::Lung<float> lung(resistance, elastance);

    ventilation::Pressure<float>    p;
    ventilation::Flow<float>        f;
    ventilation::Volume<float>      v;

    ventilation::Pressure<float>        target(20.0);
    std::chrono::duration<float>        step(1 / 1000.0);
    ventilation::control::Gain<float>   gain(0.001);
    ventilation::control::Proportional  control(gain, target);

    for (std::size_t i = 0; i < 2000; i++) {
        std::cout << p << ", " << 60.0 * f << ", " << 1000.0 * v << std::endl;

        if ((i % 1000) == 0) {
            target  = ventilation::Pressure<float>(20.0);
            control = ventilation::control::Proportional(gain, target);
        } else if ((i % 1000) == 100) {
            target  = ventilation::Pressure<float>(0.0);
            control = ventilation::control::Proportional(gain, target);
        }
        f = control(p);
        v += ventilation::integration::square(1000.0 * f, step);
        p = lung.forward(f, v);
    }
    exit(EXIT_SUCCESS);
}
