// Защита заголовка (Include Guard)
#ifndef AHT20_HEADER_FLAG
#define AHT20_HEADER_FLAG

// Импортирование компонентов системы
#include <driver/i2c_master.h>
#include <esp_err.h>
#include <esp_log.h>

// Sensor configuration structure
typedef struct
{
    i2c_master_dev_handle_t *master_bus_handle; // Preconfigured I2C bus handle
    i2c_device_config_t *dev_bus_config;        // I2C device configuration
} aht_config_t;

// Initialize AHT20 sensor
// @param aht_config sensor configuration structure
esp_err_t aht_init(aht_config_t aht_config);

// Get temperature
// @param aht_config sensor configuration structure
// @param *temperature pointer to temperature variable
esp_err_t aht_get_temperature(aht_config_t aht_config, int16_t *temperature);

// Get humidity
// @param aht_config sensor configuration structure
// @param *humidity pointer to humidity variable
esp_err_t aht_get_humidity(aht_config_t aht_config, uint8_t *humidity);
#endif