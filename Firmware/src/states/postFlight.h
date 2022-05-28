// stops logging, keep sending heartbeat message
// finish writing to flash and SD card, to avoid corruption
// play mario kart end music
#pragma once

#include "Arduino.h"
#include "state.h"
#include "../stateMachine.h"



class postFlight: public State {
    public:
        postFlight(stateMachine* sm);
        void initialise();
        State* update();
        void exitState();
};
