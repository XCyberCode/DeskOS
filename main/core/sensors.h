// Prevent reinclude
#ifndef CORE_SENSORS_HEADER_FLAG
#define CORE_SENSORS_HEADER_FLAG

// Include internal libraries
#include <inttypes.h>

// Include core components
#include <aht20.h>
#include <bmp280.h>
#include <freertos/FreeRTOS.h>

void sensor_update_task(void *pvParameters);
void sensor_get_temp(int16_t *temperature);
void sensor_get_humidity(uint8_t *humidity);
void sensor_get_pressure(uint16_t *pressure);
void sensor_get_altitude(uint16_t *altitude);
#endif