#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class gps{
    
    public:
    gps(ErrorHandler* errHand, TwoWire* I2C);
    SFE_UBLOX_GNSS myGNSS;
    ErrorHandler* _errHand;
    bool GPSBegin();
    float latitude;
    float getLatitude();
    float longitude;
    float getLongitude();
    long altitude;
    long getAltitude();
    uint8_t SIV;
    uint8_t getSIV();
    private:
    bool working = false;
    float lastTime = 0;
    TwoWire* _I2C;
};