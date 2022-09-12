// SD card logging 
#pragma once
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include "../errorHandling.h"
#include "../sensors/ADC.h"

class sd_card_log{
  public:

    sd_card_log(ADC* ads, ErrorHandler* errHand);
    //sd_card_log();
    void begin();
    void open_check();
    void logSDCard(); 
  private:
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    ErrorHandler* _errHand;
    float adcoutput[4];
    ADC* _ads;

};
