#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_ADS1115.h>
#include "ADC.h"


ADC::ADC():
ads(&Wire)
{

}

void ADC::setup(void) 
{
    Serial.begin(115200);
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
    ads.setGain(eADSGain_t::eGAIN_TWOTHIRDS);   // 2/3x gain
    ads.setMode(eMODE_SINGLE);       // single-shot mode
    ads.setRate(eRATE_128);          // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
    ads.init();
}

void ADC::loop(void) 
{
    if (ads.checkADS1115())
    {
        int16_t adc0, adc1, adc2, adc3;
        adc0 = ads.readVoltage(0);
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");
        adc1 = ads.readVoltage(1);
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");
        adc2 = ads.readVoltage(2);
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV,  ");
        adc3 = ads.readVoltage(3);
        Serial.print("A3:");
        Serial.print(adc3);
        Serial.println("mV");
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
    }

    delay(1000);
}