#pragma once
#include <Arduino.h>
#include "../src/children/logging/SDcontrol.h"
#include "../src/children/sensors/ADC.h"
#include "../src/children/errorHandling.h"

class state{
    public:
    state();
    void initialise();
    void update();
    ErrorHandler errHand;
    sd_card_log sd;
    ADC ads;
};