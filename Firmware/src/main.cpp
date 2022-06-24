#define ARDUINO_ARCH_ESP32
#include "state.h"

state flight;
uint32_t lastTimeChecked;
const uint32_t delayTime =1000;

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

#define ARDUINO_LOOP_STACK_SIZE 8192

#include <Arduino.h>


#include <exception>


TaskHandle_t loopTaskHandle = NULL;


void loopTask(void *pvParameters)
{
    flight.initialise();
    for(;;) {
        flight.update();
        vTaskDelay(1);
 
    }
}

extern "C" void app_main()
{
    initArduino(); //probably dont even need this
    xTaskCreateUniversal(loopTask, "loopTask", ARDUINO_LOOP_STACK_SIZE, NULL, 1, &loopTaskHandle, 1);
}