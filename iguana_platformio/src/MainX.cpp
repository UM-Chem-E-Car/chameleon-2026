#include "Configurations.h"

void setup() {
    program.hardware_setup_impl();
    program.software_setup_impl();
}

void loop() {
    program.spin_once();
}

