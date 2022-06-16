#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DFRobot_ADS1115.h"

class ADC{
    ADC(ErrorHandler* errHand);
    public:
    DFRobot_ADS1115 ads;
    ErrorHandler* _errHand;
    bool ADCBegin();
    void getADC();
    
    private:
    bool working = false;
};