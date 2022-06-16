#pragma once
#include <Arduino.h>
#include "../src/children/logging/SDcontrol.h"
#include "../src/children/sensors/ADC.h"
#include "../src/children/sensors/barom.h"
#include "../src/children/sensors/gps.h"
#include "../src/children/sensors/humid.h"

class state{
    public:
    state();
    void initialise();
    void update();

    ErrorHandler errHand;
    sd_card_log sd;
    ADC ads;
    barom bmp;
    gps mygps;
    humid dhtsens;

};