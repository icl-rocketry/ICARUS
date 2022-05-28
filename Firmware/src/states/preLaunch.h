// Default class on startup
// initialise sensors
// Buzz buzzer to show succesful startup
// provide a slow telemetry link
// check for launch
// Provide option for wiping and providing data on flash
#pragma once

#include "Arduino.h"
#include "state.h"
#include "children/buzzer.h"
#include "../stateMachine.h"



class preLaunch: public State {
    public:
        preLaunch(stateMachine* sm);
        void initialise();
        State* update();
        void exitState();
        buzzer buzz;
};
