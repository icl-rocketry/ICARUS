/* 
Code used to process states, and the transitions between them

Written by the Electronics team, Imperial College London Rocketry
*/
#pragma once


#include "Arduino.h"
#include "states/state.h"
#include "children/errorHandling.h"
#include "children/buzzer.h"
#include "children/logging/SDcontrol.h"
#include "children/sensors/IMU.h"
#include "children/sensors/barom.h"
#include "children/radio/radio.h"

class State;

class stateMachine {
  public:
    stateMachine();
    void initialise(State* initStatePtr);
    void update();
    void exitState();
    void changeState(State* newStatePtr);
    
    buzzer buzz;
    ErrorHandler errHand;
    IMU bno;
    barom BMP;
    sd_card_log SD_Card;
    radio loraRad;

  private:
    State* _currStatePtr;
};

