#include "commandHandler.h"

#include <vector>
#include <functional>
#include <memory>
#include "commands.h"
#include "rnp_packet.h"
#include "rnp_interface.h"
#include "commandpacket.h"
#include "TelemetryPacket.h"
#include "../children/errorHandling.h"
#include "../children/sensors/ADC.h"
#include "../children/sensors/barom.h"
#include "../children/sensors/gps.h"
#include "../children/sensors/humid.h"



CommandHandler::CommandHandler(barom* bmp388, ADC* ads, gps* myGNSS, humid* dht, ErrorHandler* errHand){
_bmp388 = bmp388;
_ads = ads;
_myGNSS = myGNSS;
_dht = dht;
_errHand = errHand;
};

void CommandHandler::handleCommand(std::unique_ptr<RnpPacketSerialized> packetptr) {


	switch (static_cast<COMMANDS>(CommandPacket::getCommand(*packetptr))) {
		case COMMANDS::Telemetry:
			TelemetryCommand(*packetptr);
			break;
		default:
			//invalid command issued DELETE IT 
			break;
			
	};
	
}

std::function<void(std::unique_ptr<RnpPacketSerialized>)> CommandHandler::getCallback() 
{
	return std::bind(&CommandHandler::handleCommand, this, std::placeholders::_1);
};


void CommandHandler::TelemetryCommand(const RnpPacketSerialized& packet) 
{
	SimpleCommandPacket commandpacket(packet);

	TelemetryPacket telemetry;


	telemetry.header.type = static_cast<uint8_t>(CommandPacket::TYPES::TELEMETRY_RESPONSE);
	telemetry.header.source = networkmanager.getAddress();
	telemetry.header.source_service = serviceID;
	telemetry.header.destination = commandpacket.header.source;
	telemetry.header.destination_service = commandpacket.header.source_service;
	telemetry.header.uid = commandpacket.header.uid; 
	telemetry.system_time = millis();

	_ads->getADC(&adcoutput[0]);

	telemetry.adc_ch1 = adcoutput[0];
	telemetry.adc_ch2 = adcoutput[1];
	telemetry.adc_ch3 = adcoutput[2];
	telemetry.adc_ch4 = adcoutput[3];

	telemetry.baro_temp = _bmp388->getTemp();
	telemetry.baro_press = _bmp388->getPressure();
	telemetry.baro_alt = _bmp388->getAltitude();

	telemetry.lat = _myGNSS->getLatitude();
	telemetry.lng = _myGNSS->getLongitude();
	telemetry.alt = _myGNSS->getAltitude();
	telemetry.siv = _myGNSS->getSIV(); 

	telemetry.dht_humid = _dht->getHumid();
	telemetry.dht_temp = _dht->getTemp();
	telemetry.dht_heatindex = _dht->getHeatIndex();

	telemetry.system_status = _errHand->get_state();

	networkmanager.sendPacket(telemetry);

}
