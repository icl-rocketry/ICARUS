// provide altitude, from pressure and temperature
//BMP388
#pragma once
#include <Arduino.h>
#include "BMP388_DEV.h"
#include "../errorHandling.h"


#define numberofmeasurements 10

class barom {
    public:
        barom(ErrorHandler* errHand, TwoWire* I2C);
        BMP388_DEV bmp388;
        ErrorHandler* _errHand;
        bool FIFOenabled;
        float altitude;
        float temperature;
        float pressure;
        uint32_t lastHasLandedTimeCheck;
        float altitudemeasurements[numberofmeasurements];

        bool baromBegin();
        //gives the altitude
        float getAltitude();
        float getTemp();
        float getPressure();
        private:
        bool working = false;

};
