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

        case states::SDCard:
            currentState |= (uint8_t)pow(2,0); 
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

