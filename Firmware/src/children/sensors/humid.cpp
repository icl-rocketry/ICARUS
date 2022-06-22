#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "humid.h"

#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
#define DHTTYPE DHT11   

humid::humid(ErrorHandler* errHand):
dht(DHT_PIN, DHTTYPE)
{
  _errHand = errHand;
}

bool humid::humidBegin(){
  Serial.println("YAy humid is working");
  Serial.begin(9600);
  dht.begin();
  working = true;
  return true ;
}

float humid::getHumid() {
    if (working) {
        if(dht.readHumidity(humidity)) {
            return humidity;
        } else {
            Serial.print("Error getting humidity");
            working = false;
            _errHand->raiseError(states::HUMIDs);
            return 0;
        }
    } else {return 0;}
}

float humid::getTemp() {
    if (working) {
        if(dht.readTemperature(temperature)) {
            return temperature;
        } else {
            Serial.print("Error getting Temperature");
            working = false;
            _errHand->raiseError(states::HUMIDs);
            return 0;
        }
    } else {return 0;}
}

float humid::getHeatIndex() {
    if (working) {
        if(dht.computeHeatIndex(temperature,humidity, false)){
           heatindex = dht.computeHeatIndex(temperature,humidity, false);
           return heatindex;
        } else {
            Serial.print("Error getting heatindex");
            working = false;
            _errHand->raiseError(states::HUMIDs);
            return 0;
        }
    } else {return 0;}
}