#include <chrono>
#include <iomanip>
#include <iostream>
#include <ventilation/ventilation.hpp>

int
main() {
    using namespace std::chrono_literals;

    ventilation::Elastance<double>   elastance(1000.0 / 30.0);
    ventilation::Resistance<double>  resistance(50.0);
    ventilation::Lung<double> lung(resistance, elastance);

    std::chrono::duration<double> step          = 100us;
    std::chrono::duration<double> simulation    = 50s;
    std::chrono::duration<double> current       = 0s;

    ventilation::cycle::Cycle cycle(
              std::chrono::duration<double>(0.6)
            , std::chrono::duration<double>(3.6)
            );
    ventilation::modes::VCV ventilator(
              ventilation::PEEP<double>(5.0)
            , ventilation::Flow<double>(1.0)
            , cycle
            );

    while (true) {
        if (current >= simulation) { break; }
        current += step;

        ventilation::Packet packet = ventilator(lung, step);
        std::cout << std::fixed << std::setprecision(4) << packet << std::endl;
    }
    exit(EXIT_SUCCESS);
}
