#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class gps{
    gps(ErrorHandler* errHand);
    public:
    SFE_UBLOX_GNSS myGNSS;
    ErrorHandler* _errHand;
    void setup();
    void loop();
};