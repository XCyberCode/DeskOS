// Include header file
#include <bmp280.h>

esp_err_t bmp280_init(bmx_config_t sensor_config) 
{
    return ESP_OK;
}

esp_err_t bmp280_get_temperature(bmx_config_t sensor_config, int16_t *temperature) 
{
    return ESP_OK;
}

esp_err_t bmp280_get_pressure(bmx_config_t sensor_config, uint16_t *pressure) 
{
    return ESP_OK;
}

esp_err_t bmp280_get_altitude(bmx_config_t sensor_config, uint16_t *altitude) 
{
    return ESP_OK;
}

esp_err_t bme280_get_humidity(bmx_config_t sensor_config, uint8_t *humidity) 
{
    return ESP_OK;
}