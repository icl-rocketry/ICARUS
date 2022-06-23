#pragma once

#include "rnp_packet.h"
#include "rnp_serializer.h"

#include <vector>

class TelemetryPacket : public RnpPacket{
    private:
    //serializer framework
        static constexpr auto getSerializer()
        {
            auto ret = RnpSerializer(
                &TelemetryPacket::adc_ch1,
                &TelemetryPacket::adc_ch2,
                &TelemetryPacket::adc_ch3,
                &TelemetryPacket::adc_ch4,
                &TelemetryPacket::baro_temp,
                &TelemetryPacket::baro_press,
                &TelemetryPacket::baro_alt,
                &TelemetryPacket::lat,
                &TelemetryPacket::lng,
                &TelemetryPacket::alt,
                &TelemetryPacket::siv,
                &TelemetryPacket::dht_humid,
                &TelemetryPacket::dht_temp,
                &TelemetryPacket::dht_heatindex,
                &TelemetryPacket::system_status,
                &TelemetryPacket::system_time
                
                

               
            );
            return ret;
        }
        
    public:
        ~TelemetryPacket();

        TelemetryPacket();
        /**
         * @brief Deserialize Telemetry Packet
         * 
         * @param data 
         */
        TelemetryPacket(const RnpPacketSerialized& packet);

        /**
         * @brief Serialize Telemetry Packet
         * 
         * @param buf 
         */
        void serialize(std::vector<uint8_t>& buf) override;

        
        //packet header
        //PacketHeader header{static_cast<uint8_t>(packet::TELEMETRY), packet_size()};
        //estimator output
        
        //adc
        float adc_ch1, adc_ch2, adc_ch3, adc_ch4;
        //barometer
        float baro_temp, baro_press,baro_alt;
        //gps
        float lat, lng, alt;
        uint8_t siv;
        //dht
        float dht_humid, dht_temp, dht_heatindex;
        //system details
        uint32_t system_status;
        uint64_t system_time;
        //radio details
        int16_t rssi; 
        float snr;


        static constexpr size_t size(){
            return getSerializer().member_size();
        }

};


