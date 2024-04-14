// Защита заголовка (Include Guard)
#ifndef CORE_SENSORS_HEADER_FLAG
#define CORE_SENSORS_HEADER_FLAG

// Подключение компонентов системы
#include <aht20.h>
#include <bmp280.h>
#include <freertos/FreeRTOS.h>
#include <sysconf.h>
#include <manager.h>
#include <string.h>
#include <esp_timer.h>

void sensor_update_task(void *task_parameters);
void sensor_get_temp(int16_t *temperature);
void sensor_get_humidity(uint8_t *humidity);
void sensor_get_pressure(uint16_t *pressure);
void sensor_get_altitude(uint16_t *altitude);
#endif