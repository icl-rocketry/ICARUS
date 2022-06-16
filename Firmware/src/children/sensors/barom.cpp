#include <Arduino.h>
#include "barom.h"
#include "BMP388_DEV.h"

#define numberofmeasurements 10
#define timestandby 80
#define altitudetolerance 3

barom::barom(ErrorHandler* errHand):
    bmp388(SDA_PIN,SCL_PIN)
 {
    FIFOenabled = false;
    _errHand = errHand;
    //starts storage of data, could put this in the hasLanded loop and run it once.
}

bool barom::baromBegin(){
    if(bmp388.begin()){
        bmp388.startNormalConversion();
        bmp388.setTimeStandby(TIME_STANDBY_80MS);
        bmp388.disableFIFO();
        //doesnt have 100ms standby
        working = true;
        return true;
    } else {
        Serial.println("Error starting bmp388");
        _errHand->raiseError(states::BAROMs);
        return false;
    }
}

float barom::getAltitude() {
    if (working) {
        if(bmp388.getAltitude(altitude)) {
            return altitude;
        } else {
            Serial.print("Error getting altitude");
            working = false;
            _errHand->raiseError(states::BAROMs);
            return 0;
        }
    } else {return 0;}
}

float barom::getTemp() {
    if (working) {
        if(bmp388.getTemperature(temperature)) {
            return temperature;
        } else {
            Serial.print("Error getting temperature");
            working = false;
            _errHand->raiseError(states::BAROMs);
            return 0;
        }
    } else {return 0;}
}
float barom::getPressure() {
    if (working) {
        if(bmp388.getPressure(pressure)) {
            return pressure;
        } else {
            Serial.print("Error getting pressure");
            working = false;
            _errHand->raiseError(states::BAROMs);
            return 0;
        }
    } else {return 0;}
}
