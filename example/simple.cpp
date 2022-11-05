#include <iostream>
#include <ventilation/ventilation.hpp>

int
main(int argc, char** argv) {
    ventilation::Pressure<double> xs(1.0);
    ventilation::Pressure<double> ys(1.0);

    xs + ys;

    exit(EXIT_SUCCESS);
}
