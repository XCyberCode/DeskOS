// Prevent reinclude
#ifndef AHT20_HEADER_FLAG
#define AHT20_HEADER_FLAG

// Include core components
#include <driver/i2c_master.h>
#include <esp_err.h>
#include <esp_log.h>

// Sensor configuration structure
typedef struct
{
    i2c_master_bus_handle_t *master_bus_handle; // Preconfigured I2C bus handle
    i2c_device_config_t *dev_bus_config;        // I2C device configuration
} ahtx_config_t;

// Initialize AHT20 sensor
// @param aht20_config sensor configuration structure
esp_err_t aht20_init(ahtx_config_t aht20_config);

// Get temperature
// @param aht20_config sensor configuration structure
// @param *temperature pointer to temperature variable
esp_err_t aht20_get_temperature(ahtx_config_t aht20_config, int16_t *temperature);

// Get humidity
// @param aht20_config sensor configuration structure
// @param *humidity pointer to humidity variable
esp_err_t aht20_get_humidity(ahtx_config_t aht20_config, uint8_t *humidity);
#endif