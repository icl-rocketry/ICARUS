#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DHT.h"

class humid{
    humid(ErrorHandler* errHand);
    public:
    DHT dht;
    ErrorHandler* _errHand;
    void setup();
    void loop();
};