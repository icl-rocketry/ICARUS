#pragma once
#include <Arduino.h>
#include "../src/children/logging/SDcontrol.h"
#include "../src/children/sensors/ADC.h"
#include "../src/children/sensors/barom.h"
#include "../src/children/sensors/gps.h"
#include "../src/children/sensors/humid.h"
#include "../src/children/errorHandling.h"
#include "../src/children/buzzer.h"

class state{
    public:
    state();
    void initialise();
    void update();
    buzzer buzz;
    ErrorHandler errHand;
    sd_card_log sd;
    ADC ads;
    barom bmp;
    gps mygps;
    humid dhtsens;

};