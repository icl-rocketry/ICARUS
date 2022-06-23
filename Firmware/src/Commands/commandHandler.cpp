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
	telemetry.pn = adcoutput[0];
	telemetry.pe = adcoutput[1];
	telemetry.pd = adcoutput[2];

	telemetry.vn = adcoutput[3];
	telemetry.ve = _bmp388->getTemp();
	telemetry.vd = _bmp388->getPressure();

	telemetry.an = _bmp388->getAltitude();
	telemetry.ae = _myGNSS->getLatitude();
	telemetry.ad = _myGNSS->getLongitude();

	telemetry.roll = _myGNSS->getAltitude();
	telemetry.pitch = _myGNSS->getSIV();
	telemetry.yaw = _dht->getHumid();

	telemetry.q0 = _dht->getTemp();
	telemetry.q1 = _dht->getHeatIndex();
	telemetry.q2 = 0;
	telemetry.q3 = 0;

	telemetry.lat = 0;
	telemetry.lng = 0;
	telemetry.alt = 0;
	telemetry.sat = 0;

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

	telemetry.baro_temp = 0;
	telemetry.baro_press = 0;
	telemetry.baro_alt = 0;

	telemetry.batt_voltage = 0;
	telemetry.batt_percent = 0;

	telemetry.launch_lat = 0;
	telemetry.launch_lng = 0;
	telemetry.launch_alt = 0;


	telemetry.system_status = _errHand->get_state();

	networkmanager.sendPacket(telemetry);

}
