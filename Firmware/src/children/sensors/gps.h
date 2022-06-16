#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

class gps{
    
    public:
    gps(ErrorHandler* errHand);
    SFE_UBLOX_GNSS myGNSS;
    ErrorHandler* _errHand;
    bool GPSBegin();
    void getGPS();
    long latitude;
    float getLatitude();
    long longitude;
    float getLongitude();
    long altitude;
    float getAltitude();
    byte SIV;
    byte getSIV();
    private:
    bool working = false;
    long lastTime = 0;
};