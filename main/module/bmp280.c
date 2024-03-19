// Include header file
#include <bmp280.h>

esp_err_t bmp_init(bmp_config_t sensor_config) 
{
    uint16_t chip_id = 0;
    uint8_t chip_id_buffer[1];
    uint8_t chip_id_send_data[1] = {0xFA};
    ESP_ERROR_CHECK(i2c_master_transmit_receive(
        *sensor_config.dev_handle, 
        chip_id_send_data, 
        1, 
        chip_id_buffer, 
        1, 
        -1
    ));
    chip_id = chip_id_buffer[0];
    return ESP_OK;
}

esp_err_t bmp_get_temperature(bmp_config_t sensor_config, int16_t *temperature) 
{
    return ESP_OK;
}

esp_err_t bmp_get_pressure(bmp_config_t sensor_config, uint16_t *pressure) 
{
    return ESP_OK;
}

esp_err_t bmp_get_altitude(bmp_config_t sensor_config, uint16_t *altitude) 
{
    return ESP_OK;
}

esp_err_t bmp_get_humidity(bmp_config_t sensor_config, uint8_t *humidity) 
{
    if(sensor_config.type == SENSOR_TYPE_BMP280)
    {
        ESP_LOGE("bmp", "Invalid sensor type");
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}