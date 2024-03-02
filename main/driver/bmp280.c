// Include header file
#include <bmp280.h>

void bmp280_init(i2c_config_t bmp280_config){}

void bmp280_get_temperature(i2c_config_t bmp280_config, int16_t *temperature){}

void bmp280_get_pressure(i2c_config_t bmp280_config, uint8_t *humidity){}

void bmp280_get_altitude(i2c_config_t bmp280_config, uint16_t *altitude){}