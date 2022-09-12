#include "Arduino.h"
#include "errorHandling.h"

ErrorHandler::ErrorHandler(){

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
            break;
        
        case states::SDCARDs:
            currentState |= (uint8_t)pow(2,4);
            
            break;

    }
}



ErrorHandler::~ErrorHandler()
{
}

