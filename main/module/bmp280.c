// Include header file
#include <bmp280.h>

void bmp280_init(bmx_config_t sensor_config) {}

void bmp280_get_temperature(bmx_config_t sensor_config, int16_t *temperature) {}

void bmp280_get_pressure(bmx_config_t sensor_config, uint16_t *pressure) {}

void bmp280_get_altitude(bmx_config_t sensor_config, uint16_t *altitude) {}

void bme280_get_humidity(bmx_config_t sensor_config, uint8_t *humidity) {}