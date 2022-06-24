#ifndef USBSEERIAL_H
#define USBSEERIAL_H

#include "rnp_interface.h"


#include <memory>
#include <vector>
#include <array>
#include <string>

#include <HardwareSerial.h>

struct USBInterfaceInfo:public RnpInterfaceInfo{
    size_t sendBufferSize;
    bool sendBufferOverflow;
    size_t receiveBufferSize;
    bool receiveBufferOverflow;
};

class USB: public RnpInterface{

    public:
        USB(HardwareSerial& serial,std::string name="Serial");
        void setup() override;
        //void send_packet(std::vector<uint8_t> &data);
        

        void sendPacket(RnpPacket& data) override;
        void update() override;
        const RnpInterfaceInfo* getInfo() override {return &_info;};

    private:
        HardwareSerial& _serial; // pointer to stream interface

        USBInterfaceInfo _info;

        std::vector<uint8_t> _sendBuffer;
        std::vector<uint8_t> _receiveBuffer;
        void checkSendBuffer();
        void getPackets();

};


#endif