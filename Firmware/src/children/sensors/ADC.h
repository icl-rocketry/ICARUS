#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DFRobot_ADS1115.h"

class ADC{
    
    public:
    ADC(ErrorHandler* errHand);
    DFRobot_ADS1115 ads;
    ErrorHandler* _errHand;
    bool ADCBegin();
    void getADC(float* ADCarray);
    int16_t adc0, adc1, adc2, adc3;
    private:
    bool working = false;
};