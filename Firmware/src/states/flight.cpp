#include "flight.h"
#include "landingLegDeploy.h"

flight::flight(stateMachine* sm):
    State(sm)
{}

void flight::initialise() {
    _sm -> buzz.stateAlert();
};

void flight::update() {
    _sm->SD_Card.logSDCard();

    // Move immediately as IMU not functioning

}

void flight::exitState() {

};