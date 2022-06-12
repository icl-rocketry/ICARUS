#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DFRobot_ADS1115.h"

class ADC{
    public:
    DFRobot_ADS1115 ads;
    void setup();
    void loop();
};