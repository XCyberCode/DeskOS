// Include internal libraries
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Include core components
#include "init.h"

void app_main(void) 
{
    xTaskCreate(init_system, "system_boot", 4096, NULL, 1, NULL);
}