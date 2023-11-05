#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ventilation/ventilation.hpp>

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
using Time          = ventilation::Time<double>;
using PCV           = ventilation::modes::PCV<double>;

int
main() {
    using namespace std::chrono_literals;

    Elastance   elastance(1000.0 / 30.0);
    Resistance  resistance(50.0);
    Lung        lung(resistance, elastance);

    Time step       = 100us;
    Time simulation = 50s;
    Time current    = 0s;

    Cycle   cycle(Time(1.0), Time(0.5), Time(3.0), Time(0.5));
    Modes   ventilator = PCV(PEEP(5.0), Peak(20.0), cycle);
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
