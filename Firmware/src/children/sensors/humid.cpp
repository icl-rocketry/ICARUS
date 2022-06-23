#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "humid.h"

#define DHTTYPE DHT11   

humid::humid(ErrorHandler* errHand):
dht(DHT_PIN, DHTTYPE)
{
  _errHand = errHand;
}

bool humid::humidBegin(){
  dht.begin();
  working = true;
  return working;
}

float humid::getHumid() {
    humidity = dht.readHumidity();
    Serial.print("dht_humidity: ");
    Serial.print(humidity);
    
    return humidity;
}

float humid::getTemp() {
    temperature = dht.readTemperature();
    Serial.print(" dht_temp: ");
    Serial.print(temperature);
    return temperature;
}

float humid::getHeatIndex() {
    if (working) {
        if(dht.computeHeatIndex(temperature,humidity, false)){
           heatindex = dht.computeHeatIndex(temperature,humidity, false);
           Serial.print(" dht_heatindex: ");
           Serial.print(heatindex);
           Serial.print("\r\n");
           return heatindex;
        } else {
            Serial.print("Error getting heatindex");
            working = false;
            _errHand->raiseError(states::HUMIDs);
            return 0;
        }
    } else {return 0;}
}