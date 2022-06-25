#include <Arduino.h>
#include <Wire.h> //Needed for I2C to GNSS
#include "gps.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS


gps::gps(ErrorHandler* errHand, TwoWire* I2C):
myGNSS()
{
    _errHand = errHand;
    _I2C = I2C;
}

bool gps::GPSBegin()
{
    if(myGNSS.begin(*_I2C, 0x42) == true){
        //Serial.println("YAY GPS is working");
        myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
        myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR
        working = true;
        return true;
    } else {
        //Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
        _errHand->raiseError(states::GPSs);
        return false;
    }
  
}

float gps::getLatitude() {
    latitude = myGNSS.getLatitude();
    return latitude;
    // if (working) {
    //     if(myGNSS.getLatitude(latitude)) {
    //       Serial.print(latitude);
    //       return latitude;
    //     } else {
    //         Serial.print("Error getting latitude");
    //         working = false;
    //         _errHand->raiseError(states::GPSs);
    //         return 0;
    //     }
    // } else {return 0;}
}
//make sure when reading to include this line to ensure reading every second 
//if (millis() - lastTime > 1000){  
//and this to update timer
//lastTime = millis(); //Update the timer

float gps::getLongitude() {
    longitude = myGNSS.getLongitude();
    return longitude;
    // if (working) {
    //     if(myGNSS.getLongitude(longitude)) {
    //       Serial.print(longitude);
    //       return longitude;
    //     } else {
    //         Serial.print("Error getting longitude");
    //         working = false;
    //         _errHand->raiseError(states::GPSs);
    //         return 0;
    //     }
    // } else {return 0;}
}

long gps::getAltitude() {
    longitude = myGNSS.getAltitude();
    return altitude;
    // if (working) {
    //     if(myGNSS.getAltitude(altitude)) {
    //       Serial.print(altitude);
    //       return altitude;
    //     } else {
    //         Serial.print("Error getting altitude");
    //         working = false;
    //         _errHand->raiseError(states::GPSs);
    //         return 0;
    //     }
    // } else {return 0;}
}

uint8_t gps::getSIV() {
    SIV = myGNSS.getSIV();
    return SIV;
    // if (working) {
    //     if(myGNSS.getSIV(SIV)) {
    //       Serial.print(SIV);
    //       return SIV;
    //     } else {
    //         Serial.print("Error getting SIV");
    //         working = false;
    //         _errHand->raiseError(states::GPSs);
    //         return 0;
    //     }
    // } else {return 0;}
}


