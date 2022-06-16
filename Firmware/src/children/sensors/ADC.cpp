#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_ADS1115.h>
#include "ADC.h"


ADC::ADC(ErrorHandler* errHand):
ads(&Wire)
{
    _errHand = errHand;
}

bool ADC::ADCBegin() 
{
    Serial.begin(115200);
    if(ads.checkADS1115()){
        ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
        ads.setGain(eADSGain_t::eGAIN_TWOTHIRDS);   // 2/3x gain
        ads.setMode(eMODE_SINGLE);       // single-shot mode
        ads.setRate(eRATE_128);          // 128SPS (default)
        ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
        ads.init();
        working = true;
        return true;
    } else {
        Serial.println("Error starting ads");
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
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");
        ADCarray++;
        adc1 = ads.readVoltage(1);
        *ADCarray = adc1;
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");
        ADCarray++;
        adc2 = ads.readVoltage(2);
        *ADCarray = adc2;
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV,  ");
        ADCarray++;
        adc3 = ads.readVoltage(3);
        *ADCarray = adc3;
        Serial.print("A3:");
        Serial.print(adc3);
        Serial.println("mV");
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
        _errHand->raiseError(states::ADCs);
    }

    delay(1000);
}
