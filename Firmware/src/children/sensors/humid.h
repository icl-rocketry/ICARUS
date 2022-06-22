#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DHT.h"

class humid{
    
    public:
    humid(ErrorHandler* errHand);
    DHT dht;
    ErrorHandler* _errHand;
    float humidity;
    float temperature;
    float heatindex;
    bool humidBegin();
    float getHumid();
    float getTemp();
    float getHeatIndex();
    private:
    bool working = false;
};