#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class gps{
    gps();
    public:
    SFE_UBLOX_GNSS myGNSS;
    void setup();
    void loop();
};