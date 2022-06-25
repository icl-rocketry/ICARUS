#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_ADS1115.h>
#include "ADC.h"


ADC::ADC(ErrorHandler* errHand, TwoWire* I2C):
ads(I2C)
{
    _errHand = errHand;
}

bool ADC::ADCBegin() 
{
    if(ads.checkADS1115()){
        //Serial.println("YAy ADS is working");
        ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
        ads.setGain(eADSGain_t::eGAIN_TWOTHIRDS);   // 2/3x gain
        ads.setMode(eMODE_SINGLE);       // single-shot mode
        ads.setRate(eRATE_128);          // 128SPS (default)
        ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
        ads.init();
        working = true;
        return true;
    } else {
        //Serial.println("Error starting ads");
        _errHand->raiseError(states::ADCs);
        return false;
    }
}

void ADC::getADC(float* ADCarray) 
{
    if (ads.checkADS1115())
    {
        adc0 = ads.readVoltage(0);
        *ADCarray = adc0;
        ADCarray++;
        adc1 = ads.readVoltage(1);
        *ADCarray = adc1;
        ADCarray++;
        adc2 = ads.readVoltage(2);
        *ADCarray = adc2;
        ADCarray++;
        adc3 = ads.readVoltage(3);
        *ADCarray = adc3;
    }
    else
    {
        _errHand->raiseError(states::ADCs);
    }

}
