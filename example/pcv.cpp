#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ventilation/ventilation.hpp>

int
main() {
    using namespace std::chrono_literals;
    using namespace ventilation::frequency::literals;

    ventilation::Elastance<double>      elastance(1000.0 / 30.0);
    ventilation::Resistance<double>     resistance(50.0);
    ventilation::lung::Forward<double>  lung(resistance, elastance);

    std::chrono::duration<double> step          = 100us;
    std::chrono::duration<double> simulation    = 50s;
    std::chrono::duration<double> current       = 0s;

    ventilation::cycle::Cycle<double> cycle(
              std::chrono::duration<double>(1.0)
            , std::chrono::duration<double>(0.5)
            , std::chrono::duration<double>(3.0)
            , std::chrono::duration<double>(0.5)
            );
    ventilation::Modes<double> ventilator = ventilation::modes::PCV<double>(
            ventilation::PEEP<double>( 5.0)             // PEEP
            , ventilation::pressure::Peak<double>(20.0) // Peak Pressure
            , cycle
            );

    ventilation::modes::visitor::Control<double> control{lung, step};

    while (true) {
        if (current >= simulation) { break; }
        current += step;

        ventilation::Packet packet = std::visit(control, ventilator);
        std::cout << std::fixed << std::setprecision(15) << packet << std::endl;
    }
    exit(EXIT_SUCCESS);
}
