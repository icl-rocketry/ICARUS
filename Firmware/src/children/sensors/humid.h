#pragma once 
#include <Arduino.h>
#include "pinDefinitions.h"
#include "../errorHandling.h"
#include "DHT.h"

class humid{
    humid();
    public:
    DHT dht;
    void setup();
    void loop();
};