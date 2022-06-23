#include "Arduino.h" 
#include "state.h"

#include "rnp_default_address.h"
#include "rnp_routingtable.h"

state::state():
buzz(),
errHand(&buzz),
sd(&bmp, &ads, &mygps, &dhtsens, &errHand),
ads(&errHand),
bmp(&errHand),
mygps(&errHand),
dhtsens(&errHand),
networkmanager(static_cast<uint8_t>(DEFAULT_ADDRESS::ROCKET),NODETYPE::LEAF,true),
lora(spi, &errHand, "Radio")
{}

void state::initialise(){
    Serial.begin(115200);
    Serial.println("Initialising classes...");
    
    // Initialise subsystems
    sd.begin();
    ads.ADCBegin();
    bmp.baromBegin();
    mygps.GPSBegin();
    dhtsens.humidBegin();
    lora.setup();

    // Set routing table
    RoutingTable flightRouting;
    flightRouting.setRoute((uint8_t)DEFAULT_ADDRESS::GROUNDSTATION,Route{2,1,{}});
    flightRouting.setRoute((uint8_t)DEFAULT_ADDRESS::DESKTOP,Route{2,2,{}});
    
    networkmanager.setRoutingTable(flightRouting);
    networkmanager.updateBaseTable(); // save the new base table

    networkmanager.setAddress(static_cast<uint8_t>(DEFAULT_ADDRESS::ROCKET));
    
    networkmanager.enableAutoRouteGen(false);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::DUMP,{});
}

void state::update(){
    sd.logSDCard();
    networkmanager.update();
}