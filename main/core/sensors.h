// Prevent reinclude
#ifndef CORE_SENSORS_HEADER_FLAG
#define CORE_SENSORS_HEADER_FLAG

// Include internal libraries
#include <inttypes.h>

void update_sensors();
int16_t sensor_get_temp();
uint8_t sensor_get_humidity();
uint16_t sensor_get_pressure();
uint16_t sensor_get_altitude();
#endif