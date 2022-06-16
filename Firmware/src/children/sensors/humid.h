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
    bool humidBegin();
    float getHumid();
    private:
    bool working = false;
};