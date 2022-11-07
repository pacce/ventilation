#include <chrono>
#include <iostream>
#include <ventilation/ventilation.hpp>

int
main(int argc, char** argv) {
    ventilation::Elastance<float>   elastance(1000.0 / 10.0);
    ventilation::Resistance<float>  resistance(30.0);
    ventilation::Lung<float> lung(resistance, elastance);

    std::chrono::duration<float>        step(1 / 1000.0);

    ventilation::cycle::Cycle cycle(
              std::chrono::duration<float>(0.1f)
            , std::chrono::duration<float>(0.2f)
            );
    ventilation::modes::PCV ventilator(
              ventilation::Pressure<float>( 5.0) // PEEP
            , ventilation::Pressure<float>(20.0) // Peak Pressure
            , cycle
            );

    for (std::size_t i = 0; i < 1000; i++) {
        ventilation::modes::Packet packet = ventilator(lung, step);
        std::cout << packet << std::endl;
    }
    exit(EXIT_SUCCESS);
}
