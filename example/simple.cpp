#include <iostream>
#include <ventilation/ventilation.hpp>

int
main(int argc, char** argv) {
    ventilation::Pressure pressure(1.1);
    std::cout << pressure << std::endl;

    exit(EXIT_SUCCESS);
}
