#include "Arduino.h" 
#include "state.h"


state::state():
errHand(),
sd( &ads,&errHand),
ads(&errHand)
{}

void state::initialise(){
    Serial.begin(115200);
    Serial.println("Initialising classes...");
    
    // Initialise subsystems
    sd.begin();
    ads.ADCBegin();

}

void state::update(){
    sd.logSDCard();

}