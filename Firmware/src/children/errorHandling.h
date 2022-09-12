// collect errors from other children
// control buzzer for errors
// provide data to other children
// Palash

#pragma once

#include "Arduino.h"

class buzzer;

// This snippet will be called any time there is an error update from any of the children. Not usable rn.
enum states
{
    ADCs = 1,SDCARDs = 5
    };

class ErrorHandler
{
public:
    uint8_t get_state(); //default state = 0 or number if there is an error
    void raiseError(states component); //will be called by the objects
    ErrorHandler();
    ~ErrorHandler();

private:
    uint8_t currentState;
};



// Not sure what to do about the sending data to other children.