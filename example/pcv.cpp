#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ventilation/ventilation.hpp>

using Mode  = ventilation::Mode<double>;
using PCV   = ventilation::modes::PCV<double>;

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
            , std::chrono::duration<double>(2.4)
            );
    std::unique_ptr<Mode> ventilator = std::make_unique<PCV>(
            ventilation::PEEP<double>( 5.0)           // PEEP
            , ventilation::pressure::Peak<double>(20.0) // Peak Pressure
            , cycle
            );

    while (true) {
        if (current >= simulation) { break; }
        current += step;

        ventilation::Packet packet = ventilator->operator()(lung, step);
        std::cout << std::fixed << std::setprecision(15) << packet << std::endl;
    }
    exit(EXIT_SUCCESS);
}
