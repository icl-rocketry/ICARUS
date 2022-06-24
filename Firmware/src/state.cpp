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
networkmanager(static_cast<uint8_t>(DEFAULT_ADDRESS::ROCKET),NODETYPE::LEAF,false),
commandhandler(&bmp,&ads,&mygps,&dhtsens,&errHand,networkmanager),
lora(spi, &errHand, "Radio"),
usb(Serial),
spi(HSPI)
{}

void state::initialise(){
    Serial.begin(115200);
    Serial.println("Initialising classes...");

    spi.begin();
    spi.setFrequency(10000000);
    Wire.begin();

    // Initialise subsystems
    sd.begin();
    ads.ADCBegin();
    // bmp.baromBegin();
    mygps.GPSBegin();
    dhtsens.humidBegin();
    lora.setup();
    usb.setup();

    networkmanager.addInterface(&usb);
    networkmanager.addInterface(&lora);

    // Set routing table
    RoutingTable flightRouting;
    flightRouting.setRoute((uint8_t)DEFAULT_ADDRESS::GROUNDSTATION,Route{2,1,{}});
    flightRouting.setRoute((uint8_t)DEFAULT_ADDRESS::DESKTOP,Route{2,2,{}});
    
    networkmanager.setRoutingTable(flightRouting);
    networkmanager.updateBaseTable(); // save the new base table

    networkmanager.setAddress(static_cast<uint8_t>(DEFAULT_ADDRESS::ROCKET));
    
    networkmanager.enableAutoRouteGen(false);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::DUMP,{});
    //register command handler callback
    networkmanager.registerService(static_cast<uint8_t>(DEFAULT_SERVICES::COMMAND),commandhandler.getCallback()); 

}

void state::update(){
    
    sd.logSDCard();
    networkmanager.update();

}