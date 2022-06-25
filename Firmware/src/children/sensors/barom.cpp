#include <Arduino.h>
#include "barom.h"
#include "BMP388_DEV.h"
#include <pinDefinitions.h>

#define numberofmeasurements 10
#define timestandby 80
#define altitudetolerance 3

barom::barom(ErrorHandler* errHand, TwoWire* I2C):
bmp388(I2C)
 {
    FIFOenabled = false;
    _errHand = errHand;
    //starts storage of data, could put this in the hasLanded loop and run it once.
}

bool barom::baromBegin(){
    bmp388.begin();
    // if(bmp388.begin()){
    //     Serial.println("YAy barom is working");
    //     bmp388.startNormalConversion();
    //     bmp388.setTimeStandby(TIME_STANDBY_80MS);
    //     bmp388.disableFIFO();
    //     //doesnt have 100ms standby
    //     working = true;
    //     return true;
    // } else {
    //     Serial.println("Error starting bmp388");
    //     _errHand->raiseError(states::BAROMs);
    //     return false;
    // }
    return true;
}

float barom::getAltitude() {
    altitude = bmp388.getAltitude(altitude);
    // if (working) {
    //     if(bmp388.getAltitude(altitude)) {
    //         return altitude;
    //     } else {
    //         Serial.print("Error getting altitude");
    //         working = false;
    //         _errHand->raiseError(states::BAROMs);
    //         return 0;
    //     }
    // } else {return 0;}
    return altitude;
}

float barom::getTemp() {
    temperature = bmp388.getTemperature(temperature);
    // if (working) {
    //     if(bmp388.getTemperature(temperature)) {
    //         return temperature;
    //     } else {
    //         Serial.print("Error getting temperature");
    //         working = false;
    //         _errHand->raiseError(states::BAROMs);
    //         return 0;
    //     }
    // } else {return 0;}
    return temperature;
}
float barom::getPressure() {
    pressure = bmp388.getPressure(pressure);
    return pressure;

    // if (working) {
    //     if(bmp388.getPressure(pressure)) {
    //         return pressure;
    //     } else {
    //         Serial.print("Error getting pressure");
    //         working = false;
    //         _errHand->raiseError(states::BAROMs);
    //         return 0;
    //     }
    // } else {return 0;}
    
}
