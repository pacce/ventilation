#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>
#include <optional>
#include <ventilation/ventilation.hpp>

using Control       = ventilation::modes::visitor::Control<double>;
using Cycle         = ventilation::cycle::Cycle<double>;
using Elastance     = ventilation::Elastance<double>;
using Flow          = ventilation::Flow<double>;
using Lung          = ventilation::lung::Forward<double>;
using Modes         = ventilation::Modes<double>;
using Packet        = ventilation::Packet<double>;
using PEEP          = ventilation::PEEP<double>;
using Resistance    = ventilation::Resistance<double>;
using Time          = ventilation::Time<double>;
using VCV           = ventilation::modes::VCV<double>;

int
main() {
    using namespace std::chrono_literals;

    Elastance   elastance(1000.0 / 30.0);
    Resistance  resistance(50.0);
    Lung        lung(resistance, elastance);

    Time step       = 100us;
    Time simulation = 50s;
    Time current    = 0s;

    Cycle   cycle(Time(0.6), Time(0.4), Time(3.2), {});
    Modes   ventilator = VCV(PEEP(10.0), Flow(1.0), cycle);
    Control control{lung, step};

    while (true) {
        if (current >= simulation) { break; }
        current += step;

        std::cout   << std::fixed
                    << std::setprecision(15)
                    << std::visit(control, ventilator)
                    << std::endl
                    ;
    }
    exit(EXIT_SUCCESS);
}
