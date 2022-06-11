#include <Arduino.h>
#include <ADS131M04.h>
#include "ADC.h"
#include "registerDefinitions.h"

//ADC::ADC(ErrorHandler* errHand):
//    ads(ADC_CS, ADC_CLK, spi, 1)
//{
//    _errHand errHand;
//};

bool ADC::ADCBegin(){
    ads.begin();
    if(initialised){
        working = true;
        return true;
    } else {
        Serial.println('Error starting ADC');
        //_errHand->raiseError(states::Baro);
        return false;
    }
}