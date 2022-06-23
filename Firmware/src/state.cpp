#include "Arduino.h" 
#include "state.h"


state::state():
buzz(),
errHand(&buzz),
sd(&bmp, &ads, &mygps, &dhtsens, &errHand),
ads(&errHand),
bmp(&errHand),
mygps(&errHand),
dhtsens(&errHand),
networkmanager(),
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

}

void state::update(){
    sd.logSDCard();
    networkmanager.update();
}