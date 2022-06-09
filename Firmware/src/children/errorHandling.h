// collect errors from other children
// control buzzer for errors
// provide data to other children
// Palash

#pragma once

#include "Arduino.h"
#include "buzzer.h"

class buzzer;

// This snippet will be called any time there is an error update from any of the children. Not usable rn.
enum states
{
    SDCard = 1// IMU not used as conflicts with IMU class
};

class ErrorHandler
{
public:
    uint8_t get_state(); //default state = 0 or number if there is an error
    void raiseError(states component); //will be called by the objects
    void BuzzMe(); //buzzer to be activated
    ErrorHandler(buzzer* buzz);
    ~ErrorHandler();

private:
    uint8_t currentState;
    buzzer* _buzz;
};



// Not sure what to do about the sending data to other children.