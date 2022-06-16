#include "Arduino.h" 
#include "state.h"

state::state():
buzz(),
errHand(&buzz),
sd(&bmp, &ads, &mygps, &dhtsens, &errHand),
ads(&errHand),
bmp(&errHand),
mygps(&errHand),
dhtsens(&errHand)
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

}

void state::update(){
    sd.logSDCard();

}