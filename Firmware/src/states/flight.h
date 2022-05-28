// start logging and sending telemetry and errors full force (10Hz)
// check for landing

#pragma once

#include "Arduino.h"
#include "state.h"
#include "children/buzzer.h"
#include "stateMachine.h"


class flight: public State {
    public:
        flight(stateMachine* sm);
        void initialise();
        State* update();
        void exitState();
};
