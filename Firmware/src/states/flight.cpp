#include "flight.h"

flight::flight(stateMachine* sm):
    State(sm)
{}

void flight::initialise() {
    _sm -> buzz.stateAlert();
};

State* flight::update() {
    _sm->SD_Card.logSDCard();

    // Move immediately as IMU not functioning

    return nullptr;
}

void flight::exitState() {

};