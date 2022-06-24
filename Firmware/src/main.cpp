#define ARDUINO_ARCH_ESP32
#include <Arduino.h>
#include "state.h"

state flight;
uint32_t lastTimeChecked;
const uint32_t delayTime =0;

void setup() {
    flight.initialise();
    lastTimeChecked = millis();
}

void loop() {
    if ( (millis()-lastTimeChecked) > delayTime){
        flight.update();
        lastTimeChecked = millis();
    }
    
}