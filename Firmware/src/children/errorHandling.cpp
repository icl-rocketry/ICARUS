#include "Arduino.h"
#include "errorHandling.h"
#include "buzzer.h"

ErrorHandler::ErrorHandler(buzzer* buzz){
    _buzz = buzz;
    currentState = 0;

}

uint8_t ErrorHandler::get_state(){
    //getter function
    return currentState; 
}

void ErrorHandler::raiseError(states component){
    switch (component)
    {

        case states::ADCs:
            currentState |= (uint8_t)pow(2,0); 
            BuzzMe();
            break;

        case states::BAROMs:
            currentState |= (uint8_t)pow(2,1); 
            BuzzMe();
            break;

        case states::HUMIDs:
            currentState |= (uint8_t)pow(2,2); 
            break;

        case states::GPSs:
            currentState |= (uint8_t)pow(2,3); 
            BuzzMe();
            break;
        
        case states::SDCARDs:
            currentState |= (uint8_t)pow(2,4); 
            BuzzMe();
            break;
            
        case states::LoRas:
            currentState |= (uint8_t)pow(2,5); 
            BuzzMe();
            break;

    }
}

void ErrorHandler::BuzzMe(){
    _buzz -> errorAlert();
}

ErrorHandler::~ErrorHandler()
{
}

