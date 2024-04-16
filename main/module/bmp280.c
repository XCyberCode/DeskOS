// Подключение заголовочного файла
#include <bmp280.h>

void bmp_compensate_pressure(bmp_config_t sensor_config, int32_t raw_pressure, int32_t raw_temp, double *pressure)
{
    // Осуществление компенсации измерений атмосферного давления
    // посредством данных, прочитанных из калибровочных регистров
    double calib_var1, calib_var2, current_pressure;
    calib_var1 = ((double)raw_temp / 2.0) - 64000.0;
    calib_var2 = calib_var1 * calib_var1 * ((double)sensor_config.calibration_data.P6) / 32768.0;
    calib_var2 = calib_var2 + calib_var1 * ((double)sensor_config.calibration_data.P5) * 2.0;
    calib_var2 = (calib_var2 / 4.0) + (((double)sensor_config.calibration_data.P4) * 65536.0);
    calib_var1 = (((double)sensor_config.calibration_data.P3) * calib_var1 * calib_var1 / 524288.0 + 
        ((double)sensor_config.calibration_data.P2) * calib_var1) / 524288.0;
    calib_var1 = (1.0 + calib_var1 / 32768.0) * ((double)sensor_config.calibration_data.P1);
    
    // Предотвращение деления на ноль
    if (calib_var1 == 0.0) 
    {
        *pressure = 0;
    }
    else
    {
        current_pressure = 1048576.0 - (double)raw_pressure;
        current_pressure= (current_pressure - (calib_var2 / 4096.0)) * 6250.0 / calib_var1;
        calib_var1 = ((double)sensor_config.calibration_data.P9) * current_pressure * current_pressure / 2147483648.0;
        calib_var2 = current_pressure * ((double)sensor_config.calibration_data.P8) / 32768.0;
        current_pressure = current_pressure + (calib_var1 + calib_var2 + ((double)sensor_config.calibration_data.P7)) / 16.0;
        *pressure = current_pressure;
    }
}

void bmp_compensate_temperature(bmp_config_t sensor_config, int32_t raw_temp, int32_t *temperature)
{
    // Осуществление компенсации измерений температуры
    // посредством данных, прочитанных из калибровочных регистров
    double calib_var1 = (((double)raw_temp) / 16384.0 - ((double)sensor_config.calibration_data.T1) / 1024.0) * ((double)sensor_config.calibration_data.T2);
    double calib_var2 = ((((double)raw_temp) / 131072.0 - ((double)sensor_config.calibration_data.T1) / 8192.0) *
    (((double)raw_temp) / 131072.0 - ((double)sensor_config.calibration_data.T1) / 8192.0)) * ((double)sensor_config.calibration_data.T3);
    *temperature = (int32_t)(calib_var1 + calib_var2);
}

esp_err_t bmp_init(bmp_config_t *sensor_config) 
{
    // Подготовка к передачи данных
    uint8_t transmit_data[2] = {BMP280_REG_CHIP_ID};
    uint8_t received_data[1] = {0};

    // Получение ID чипа из памяти датчика
    // 0x60 - BME280, 0x58 - BMP280
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config->dev_handle, received_data, 1, -1));
    if(received_data[0] != 0x60 && received_data[0] != 0x58)
    {
        ESP_LOGE("bmp", "Incorect ChipID of the sensor. ChipID: %#x", received_data[0]);
        return ESP_ERR_NOT_FOUND;
    }

    // Осуществление программной перезагрузки датчика
    transmit_data[0] = BMP280_REG_RESET;
    transmit_data[1] = BMP280_RESET_VALUE;
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 1, -1));
    
    // Ожидание датчика
    vTaskDelay(100 / portTICK_PERIOD_MS);

    // Получение калибровочных данных с датчика
    bmp_read_calibration_data(sensor_config);

    // Настройка фильтра и задержки между измерениями
    transmit_data[0] = BMP280_REG_CONFIG;
    transmit_data[1] = (sensor_config->standby_time << 5) | (sensor_config->filter << 2);
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 2, -1));
    
    // Настройка оверсемплинга (oversample) и режима работы
    transmit_data[0] = BMP280_REG_CONTROL;
    transmit_data[1] = (sensor_config->osrs_temp << 5) | (sensor_config->osrs_press << 2) | (sensor_config->mode);
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 2, -1));

    // Вернуть состояние
    return ESP_OK;
}

esp_err_t bmp_read_calibration_data(bmp_config_t *sensor_config)
{
    // Чтение калибровочных данных. Эти данные необходимы для компенсации измерений
    uint8_t transmit_data[1] = {BMP280_REG_CALIBRATE};
    uint8_t received_data[24];
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config->dev_handle, transmit_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config->dev_handle, received_data, 24, -1));
    sensor_config->calibration_data.T1 = (received_data[0] | (received_data[1] << 8));
    sensor_config->calibration_data.T2 = (received_data[2] | (received_data[3] << 8));
    sensor_config->calibration_data.T3 = (received_data[4] | (received_data[5] << 8));
    sensor_config->calibration_data.P1 = (received_data[6] | (received_data[7] << 8));
    sensor_config->calibration_data.P2 = (received_data[8] | (received_data[9] << 8));
    sensor_config->calibration_data.P3 = (received_data[10] | (received_data[11] << 8));
    sensor_config->calibration_data.P4 = (received_data[12] | (received_data[13] << 8));
    sensor_config->calibration_data.P5 = (received_data[14] | (received_data[15] << 8));
    sensor_config->calibration_data.P6 = (received_data[16] | (received_data[17] << 8));
    sensor_config->calibration_data.P7 = (received_data[18] | (received_data[19] << 8));
    sensor_config->calibration_data.P8 = (received_data[20] | (received_data[21] << 8));
    sensor_config->calibration_data.P9 = (received_data[22] | (received_data[23] << 8));
    return ESP_OK;
}

esp_err_t bmp_read_raw_temperature(bmp_config_t sensor_config, int32_t *temperature) 
{
    // Чтение "сырых" данных о температуре с датчика
    uint8_t transmit_data[1] = {BMP280_REG_TEMP_MSB};
    uint8_t received_data[3];
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config.dev_handle, transmit_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config.dev_handle, received_data, 3, -1));
    int32_t raw_temp = ((uint32_t)received_data[0] << 16) | ((uint32_t)received_data[1] << 8) | (uint32_t)received_data[2];
    raw_temp >>= 4; // Сдвиг. Необходим для MSB, LSB и XLSB

    // Осуществить компенсацию температуры
    bmp_compensate_temperature(sensor_config, raw_temp, temperature);

    // Вернуть состояние
    return ESP_OK;
}

esp_err_t bmp_read_temperature(bmp_config_t sensor_config, double *temperature)
{
    int32_t raw_temp;
    bmp_read_raw_temperature(sensor_config, &raw_temp);
    *temperature = raw_temp / 5120.0;

    // Return state
    return ESP_OK;
}

esp_err_t bmp_read_pressure(bmp_config_t sensor_config, double *pressure) 
{
    // Чтение необработанных данных о температуре с датчика
    int32_t raw_temp;
    ESP_ERROR_CHECK(bmp_read_raw_temperature(sensor_config, &raw_temp));

    // Чтение "сырых" дынных о давлении с датчика
    uint8_t transmit_data[1] = {BMP280_REG_PRESS_MSB};
    uint8_t received_data[3];
    ESP_ERROR_CHECK(i2c_master_transmit(sensor_config.dev_handle, transmit_data, 1, -1));
    ESP_ERROR_CHECK(i2c_master_receive(sensor_config.dev_handle, received_data, 3, -1));
    int32_t raw_press = (received_data[0] << 16) | (received_data[1] << 8) | received_data[2];
    raw_press >>= 4; // Сдвиг. Необходим для MSB, LSB и XLSB

    // Осуществить компенсацию давления
    bmp_compensate_pressure(sensor_config, raw_press, raw_temp, pressure);

    // Вернуть состояние
    return ESP_OK;
}

esp_err_t bmp_get_altitude(bmp_config_t sensor_config, uint16_t *altitude) 
{
    // Вернуть результат выполнения
    return ESP_OK;
}

esp_err_t bmp_read_humidity(bmp_config_t sensor_config, uint8_t *humidity) 
{
    if(sensor_config.type == SENSOR_TYPE_BMP280)
    {
        ESP_LOGE("bmp", "Invalid sensor type");
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}