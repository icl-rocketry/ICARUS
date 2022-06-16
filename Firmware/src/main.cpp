#define ARDUINO_ARCH_ESP32
#include <Arduino.h>
#include "state.h"

state flight;

void setup() {
    flight.initialise();
}

void loop() {
    flight.update();
}