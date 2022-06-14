// landing alert, startup tune
// Error tunes
// buzz when changing state

#pragma once
#include "children/errorHandling.h"
#include <Arduino.h>
#include "pinDefinitions.h"
#include <vector>




struct Note_t{
    uint16_t frequency;
    uint16_t duration;
};

class buzzer{
    public:
        buzzer();
        // set up the buzzer
        void setupBuzzer();
        // alert sound with starting
        void startingAlert();
        // alert sound when there's an error
        void errorAlert();

        //update function
        void update();

    private:
        std::vector<Note_t> noteBuffer;
        Note_t currentNote;
        
        unsigned long previousT;
};

