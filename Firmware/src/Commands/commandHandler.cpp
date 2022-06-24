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



CommandHandler::CommandHandler(barom* bmp388, ADC* ads, gps* myGNSS, humid* dht, ErrorHandler* errHand,RnpNetworkManager& netman):
networkmanager(netman)
{
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
	telemetry.pn = 0;
	telemetry.pe = 0;
	telemetry.pd = 0;

	telemetry.vn = 0;
	telemetry.ve = 0;
	telemetry.vd = 0;

	telemetry.an = 0;
	telemetry.ae = 0;
	telemetry.ad = 0;

	telemetry.roll = _dht->getTemp();
	telemetry.pitch = _dht->getHeatIndex();
	telemetry.yaw = _dht->getHumid();

	telemetry.q0 = adcoutput[0];
	telemetry.q1 = adcoutput[1];
	telemetry.q2 = adcoutput[2];
	telemetry.q3 = adcoutput[3];

	telemetry.lat = _myGNSS->getLatitude();
	telemetry.lng = _myGNSS->getLongitude();
	telemetry.alt = _myGNSS->getAltitude();
	telemetry.sat = _myGNSS->getSIV();

	telemetry.ax = 0;
	telemetry.ay = 0;
	telemetry.az = 0;

	telemetry.h_ax = 0;
	telemetry.h_ay = 0;
	telemetry.h_az = 0;

	telemetry.gx = 0;
	telemetry.gy = 0;
	telemetry.gz = 0;

	telemetry.mx = 0;
	telemetry.my = 0;
	telemetry.mz = 0;

	telemetry.baro_temp = _bmp388->getTemp();
	telemetry.baro_press = _bmp388->getPressure();
	telemetry.baro_alt = _bmp388->getAltitude();

	telemetry.batt_voltage = 0;
	telemetry.batt_percent = 0;

	telemetry.launch_lat = 0;
	telemetry.launch_lng = 0;
	telemetry.launch_alt = 0;


	telemetry.system_status = _errHand->get_state();

	networkmanager.sendPacket(telemetry);

}
