// provide altitude, from pressure and temperature
//BMP388
#pragma once
#include <Arduino.h>
#include "BMP388_DEV.h"
#include "../errorHandling.h"


#define numberofmeasurements 10

class barom {
    public:
        barom(ErrorHandler* errHand);
        BMP388_DEV bmp388;
        ErrorHandler* _errHand;
        bool FIFOenabled;
        float altitude;
        uint32_t lastHasLandedTimeCheck;
        float altitudemeasurements[numberofmeasurements];

        bool baromBegin();
        bool working = false;
        //gives the altitude
        float getAltitude();

};
