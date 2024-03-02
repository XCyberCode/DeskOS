// Prevent reinclude
#ifndef LIB_BMP280_HEADER_FLAG
#define LIB_BMP280_HEADER_FLAG

// Include core components
#include <driver/i2c.h>

// Initialize BMP280 sensor
// @param bmp280_config structure with sensor configuration
void bmp280_init(i2c_config_t bmp280_config);

// Get temperature
// @param bmp280_config structure with sensor configuration
// @param *temperature pointer to temperature variable
void bmp280_get_temperature(i2c_config_t bmp280_config, int16_t *temperature);

// Get humidity
// @param bmp280_config structure with sensor configuration
// @param *temperature pointer to humidity variable
void aht20_get_humidity(i2c_config_t bmp280_config, uint8_t *humidity);

// Get altitude
// @param bmp280_config structure with sensor configuration
// @param *altitude pointer to altitude variable
void bmp280_get_altitude(i2c_config_t bmp280_config, uint16_t *altitude);
#endif