#include "radio.h"
#include <LoRa.h>
#include <SPI.h>
#include <Arduino.h>
#include <vector>

radio::radio(barom* bmp388, ADC* ads, gps* maxm8q, humid* dht11, ErrorHandler* errHand):
_txDone(false),
_errHand(errHand),
_bmp(bmp388),
_ads(ads),
_maxm8q(maxm8q),
_dht11(dht11)
{}


void radio::setup() {
    // Code to be run at setup

    LoRa.setPins(RADIO_CS, RADIO_RESET, RADIO_IRQ);

    // Initialise LoRa
    if (!LoRa.begin(868E6)) {
        _errHand->raiseError(states::LoRas);
    }
}

void radio::update() {
    // Code to be run every loop

    checkIncomming();
    checkSendBuffer();
    checkTx();
}

void radio::checkIncomming(){
    // Check if the radio is currently transmitting, and abort if it is
    if (!_txDone) {
        Serial.println("Transmitting...");
        return;
    }

    // Check if there's a new packet incoming
    int packetSize = LoRa.parsePacket();

    if (packetSize != 0) {
        // Read the header
        Serial.println("Received Packet!");
        response_time = millis();
        // Read and then parse the command
        parseCommand(LoRa.read());
    }
}

void radio::sendTelemetry() {
    // Sends data to GCS over LoRa
   updateTelemetry();
    _sendBuffer.push_back(telemetryPacket); // copies telemetry into packet bufffer
    Serial.println("Added packet to buffer");
    msgCount++;
}


void radio::checkSendBuffer(){

    if (!(_sendBuffer.size() > 0)){
        return; // exit if nothing in the buffer
    }

    if (millis()-response_time > RESPONSE_DELAY) { // wait before sending
        // check if radio is busy, if it isnt then send next packet
        if(LoRa.beginPacket()){ 
            Serial.println("Sending packet...");
            telemetry_t packet = _sendBuffer.front();
            LoRa.write((uint8_t*)&packet, telemetryPacketLength);
            LoRa.endPacket(true); // asynchronous send 
            //delete front element of send buffer
            _sendBuffer.erase(_sendBuffer.begin());
            _txDone = false;
        }
    }
}

void radio::checkTx(){
    if (_txDone){
        return;
    }
    if (!LoRa.isTransmitting()){
        _txDone = true;
    }
}


void radio::parseCommand(uint8_t command) {
    // Function that updates the spike variables based on the received command

    switch (command) {
        case TELEMETRY_COMMAND:
            sendTelemetry();
            break;

        default:
            // Poorly formatted command received!
            break;
    }
    
}

void radio::updateTelemetry() {
    telemetryPacket.systemState = _errHand->get_state();
    telemetryPacket.altitude = _bmp->getAltitude();
    telemetryPacket.systemTime = millis();
}