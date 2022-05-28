#include "postFlight.h"

postFlight::postFlight(stateMachine* sm):
State(sm)
{}

void postFlight::initialise() {
    _sm -> buzz.stateAlert();
    _sm -> buzz.errorAlert();
};

State* postFlight::update() {
    return this;
};

void postFlight::exitState() {

};