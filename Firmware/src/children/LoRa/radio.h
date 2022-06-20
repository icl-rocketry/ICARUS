// Collects and sends data to GCS
// Receive commands from GCS for spike
#pragma once
// Define the meaning of different received commands
#define TELEMETRY_COMMAND 0x01

#define telemetryPacketLength 25

#define RESPONSE_DELAY 1000 // Wait before response in ms

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include <array>
#include <vector>
#include <pinDefinitions.h>
#include "../errorHandling.h"
#include "../sensors/ADC.h"
#include "../sensors/barom.h"
#include "../sensors/gps.h"
#include "../sensors/humid.h"


// Telemetry packet struct
struct telemetry_t{
    uint8_t systemState;
    float altitude;
    uint32_t systemTime;
}__attribute__((__packed__)); 

class radio {
    public:
        radio(barom* bmp388, ADC* ads, gps* maxm8q, humid* dht11, ErrorHandler* errHand);
        void setup();
        void update();

        telemetry_t telemetryPacket;
       void sendTelemetry();

    private:
        void parseCommand(uint8_t command);
        void checkIncomming();
        void checkSendBuffer();
        void checkTx();
        void updateTelemetry();

        std::vector<telemetry_t> _sendBuffer;
        bool _txDone;
        uint16_t msgCount;
        ErrorHandler* _errHand;
        barom* _bmp;
        ADC* _ads;
        gps* _maxm8q;
        humid* _dht11;
        uint32_t response_time;
};

