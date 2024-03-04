// Prevent reinclude
#ifndef AHT20_HEADER_FLAG
#define AHT20_HEADER_FLAG

// Include core components
#include <driver/i2c.h>
#include <esp_err.h>
#include <esp_log.h>

// Sensor configuration structure
typedef struct
{
    i2c_config_t bus_config; // I2C bus config
} ahtx_config_t;

// Initialize AHT20 sensor
// @param aht20_config sensor configuration structure
void aht20_init(i2c_config_t aht20_config);

// Get temperature
// @param aht20_config sensor configuration structure
// @param *temperature pointer to temperature variable
void aht20_get_temperature(i2c_config_t aht20_config, int16_t *temperature);

// Get humidity
// @param aht20_config sensor configuration structure
// @param *humidity pointer to humidity variable
void aht20_get_humidity(i2c_config_t aht20_config, uint8_t *humidity);
#endif