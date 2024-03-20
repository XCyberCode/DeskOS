// Include header file
#include <bmp280.h>

esp_err_t bmp_init(bmp_config_t *sensor_config) 
{
    // Prepare for transmission
    uint8_t register_data[1] = {BMP280_REG_CHIP_ID};
    uint8_t control_data[1] = {0};
    uint8_t received_data[1] = {0};

    // Get chip_id of the sensor
    // 0x60 - BME280, 0x58 - BMP280
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, register_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config->dev_handle, received_data, 1, -1));
    if(received_data[0] != 0x60 && received_data[0] != 0x58)
    {
        ESP_LOGE("bmp", "Incorect ChipID of the sensor. ChipID: %#x", received_data[0]);
        return ESP_ERR_NOT_FOUND;
    }
    
    // Prepare sensor
    bmp_read_calibration_data(sensor_config);

    // Configure oversampling and working mode
    register_data[0] = BMP280_REG_CONTROL;
    control_data[0] = (sensor_config->osrs_temp << 5) | (sensor_config->osrs_press << 2) | sensor_config->mode;
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, register_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, control_data, 1, -1));
    // Configure filtering and the delay between measurements
    register_data[0] = BMP280_REG_CONFIG;
    control_data[0] = (sensor_config->standby_time << 5) | (sensor_config->filter << 2);
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, register_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, control_data, 1, -1));

    return ESP_OK;
}

esp_err_t bmp_read_calibration_data(bmp_config_t *sensor_config)
{
    uint8_t register_data[1] = {BMP280_REG_CALIBRATE};
    uint8_t received_data[24];
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, register_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config->dev_handle, received_data, 24, -1));
    sensor_config->calibation_data.T1 = (received_data[0] | (received_data[1] << 8));
    sensor_config->calibation_data.T2 = (received_data[2] | (received_data[3] << 8));
    sensor_config->calibation_data.T3 = (received_data[4] | (received_data[5] << 8));
    sensor_config->calibation_data.P1 = (received_data[6] | (received_data[7] << 8));
    sensor_config->calibation_data.P2 = (received_data[8] | (received_data[9] << 8));
    sensor_config->calibation_data.P3 = (received_data[10] | (received_data[11] << 8));
    sensor_config->calibation_data.P4 = (received_data[12] | (received_data[13] << 8));
    sensor_config->calibation_data.P5 = (received_data[14] | (received_data[15] << 8));
    sensor_config->calibation_data.P6 = (received_data[16] | (received_data[17] << 8));
    sensor_config->calibation_data.P7 = (received_data[18] | (received_data[19] << 8));
    sensor_config->calibation_data.P8 = (received_data[20] | (received_data[21] << 8));
    sensor_config->calibation_data.P9 = (received_data[22] | (received_data[23] << 8));
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