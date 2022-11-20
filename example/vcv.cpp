#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ventilation/ventilation.hpp>

using Mode  = ventilation::modes::Base<double>;
using VCV   = ventilation::modes::VCV<double>;

int
main() {
    using namespace std::chrono_literals;

    ventilation::Elastance<double>      elastance(1000.0 / 30.0);
    ventilation::Resistance<double>     resistance(50.0);
    ventilation::lung::Forward<double>  lung(resistance, elastance);

    std::chrono::duration<double> step          = 100us;
    std::chrono::duration<double> simulation    = 50s;
    std::chrono::duration<double> current       = 0s;

    ventilation::cycle::Cycle cycle(
              std::chrono::duration<double>(0.6)
            , std::chrono::duration<double>(3.6)
            );
    std::unique_ptr<Mode> ventilator = std::make_unique<VCV>(
              ventilation::PEEP<double>(10.0)   // PEEP
            , ventilation::Flow<double>( 1.0)   // Peak Flow
            , cycle
            );

    while (true) {
        if (current >= simulation) { break; }
        current += step;

        ventilation::Packet packet = ventilator->operator()(lung, step);
        std::cout << std::fixed << std::setprecision(4) << packet << std::endl;
    }
    exit(EXIT_SUCCESS);
}
