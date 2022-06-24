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
    int32_t latitude;
    int32_t getLatitude();
    int32_t longitude;
    int32_t getLongitude();
    int32_t altitude;
    int32_t getAltitude();
    uint8_t SIV;
    uint8_t getSIV();
    private:
    bool working = false;
    long lastTime = 0;
    TwoWire* _I2C;
};