// BEWARE
// I don't know what I am doing

#include "buzzer.h"
#include "driver/ledc.h"
#include "pinDefinitions.h"

buzzer::buzzer():
    previousT(0)
{
   noteBuffer.reserve(10); 
}

void buzzer::setupBuzzer(){
    // ESP_tone.setCompatibleMode(true);
    ledcSetup(0,0,8);
    ledcAttachPin(BUZZER_PIN,0);
    ledcWrite(0,255); //MAXIMUM volume
    ledcWriteTone(0,0); //write 0 hz so no noise
}


// called in the error handling code
void buzzer::errorAlert(){
    //// wouldn't shut up before the error is fixed
    noteBuffer.push_back(Note_t{1000,10000}); // 10 second
   
}


void buzzer::update()
{
    if (millis() - previousT > currentNote.duration)
    {
        previousT = millis(); // update previous time

        if (noteBuffer.size() == 0)
        { // check size of note buffer
            // write zero to ledc
            ledcWriteTone(0, 0);
            return;
        }
        // pop from note buffer to get next note
        currentNote = noteBuffer.front();
        noteBuffer.erase(noteBuffer.begin()); // remove from note buffer
        // ledc play note
    }
    ledcWriteTone(0, currentNote.frequency);
}

/*

cool music
https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8

*/