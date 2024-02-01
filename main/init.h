#include <freertos/task.h>
#include <freertos/FreeRTOS.h>

// Include core components
#include "led_matrix.h"

void init_system(void *pvParameters)
{
    led_matrix_init();
    vTaskDelete(NULL);
}