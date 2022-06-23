//process commands stored in command buffer and execute

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "commands.h"
#include "rnp_packet.h"
#include "rnp_networkmanager.h"
#include "commandpacket.h"
#include "../children/errorHandling.h"
#include "../children/sensors/ADC.h"
#include "../children/sensors/barom.h"
#include "../children/sensors/gps.h"
#include "../children/sensors/humid.h"


class CommandHandler {
    public:
        CommandHandler(barom* bmp388, ADC* ads, gps* myGNSS, humid* dht, ErrorHandler* errHand);
        
        std::function<void(std::unique_ptr<RnpPacketSerialized>)> getCallback();

        static constexpr uint8_t serviceID = static_cast<uint8_t>(DEFAULT_SERVICES::COMMAND); // serivce ID for network manager
        RnpNetworkManager networkmanager;   
    private:
        float adcoutput[4];
        ErrorHandler* _errHand;
        barom* _bmp388;
        ADC* _ads;
        gps* _myGNSS;
        humid* _dht;
        void handleCommand(std::unique_ptr<RnpPacketSerialized> packetptr);
        void TelemetryCommand(const RnpPacketSerialized& packet);

};	
