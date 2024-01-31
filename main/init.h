#include <freertos/task.h>
#include <freertos/FreeRTOS.h>

void init_system(void *pvParameters)
{
    init_led_strip();
    vTaskDelete(NULL);
}