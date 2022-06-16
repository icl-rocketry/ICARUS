#include "SDcontrol.h"
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include "pinDefinitions.h"


sd_card_log::sd_card_log(barom* bmp388, ADC* ads, gps* myGNSS, humid* dht, ErrorHandler* errHand){
//sd_card_log::sd_card_log(){
  _bmp388 = bmp388;
  _ads = ads;
  _myGNSS = myGNSS;
  _dht = dht;
  _errHand = errHand;
};

void sd_card_log::begin(){
    SD.begin(SD_CS);

    if (!SD.begin(SD_CS))
    {
        Serial.println("Card Mount Failed");
        _errHand->raiseError(states::SDCARDs);
        return;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        _errHand->raiseError(states::SDCARDs);
        return;
    }
    Serial.println("Initializing SD card...");
    if (!SD.begin(SD_CS))
    {
        Serial.println("ERROR - SD card initialization failed!");
        _errHand->raiseError(states::SDCARDs);
        return; // init failed
    }
}

void sd_card_log::open_check(){
File file = SD.open("/data.txt");
if (!file)
{
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "MillisTime, Altitude, Orr_real, Orr_i, orr_j, orr_k, SystemState\r\n");
}
else
{
    Serial.println("File already exists");
}
file.close();
}

void sd_card_log::logSDCard(){

  // Get values to write
  unsigned long timeStamp = millis();

  pressure = _bmp388->getPressure();
//Need to add the data message here SC21
// check vlad for insp SC21
// the data that needs to be
 
  // Arbitrary numbers for testing
  uint8_t SystemState = _errHand->get_state();

  String dataMessage;
  dataMessage = String(timeStamp) + "," +         
                "," + String(SystemState) + "\r\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}

void sd_card_log::appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    _errHand->raiseError(states::SDCARDs);
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
    _errHand->raiseError(states::SDCARDs);
  }
  file.close();
}

void sd_card_log::writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    _errHand->raiseError(states::SDCARDs);
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
    _errHand->raiseError(states::SDCARDs);
  }
  file.close();
}
