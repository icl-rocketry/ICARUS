#pragma once
#include <Arduino.h>
#include <vector>
#include "children/errorHandling.h"
#include "ADS131M04.h"

class ADC {
    public:
    ADC(ErrorHandler* errHand);
    ADS131M04 ads;
    ErrorHandler* _errHand;

    bool ADCBegin();
    bool working = false;
    float current;
};