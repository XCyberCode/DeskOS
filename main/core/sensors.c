// Include header file
#include <sensors.h>

// Include core libraries
#include <sysconf.h>

void sensor_update_task(void *pvParameters)
{
    i2c_master_bus_config_t i2c_master_bus_config = {
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t i2c_master_bus_handle;
    
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_bus_config, &i2c_master_bus_handle));

    i2c_device_config_t bmp_dev_config = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SENSOR_BMPX80_ADDRESS,
        .scl_speed_hz = I2C_DEFAULT_SPEED_HZ
    };
    i2c_master_dev_handle_t bmp_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_master_bus_handle, &bmp_dev_config, &bmp_handle));

    bmp_config_t bmp_config = 
    {
        .dev_handle = bmp_handle,
        .type = SENSOR_TYPE_BMP280,
        .mode = BMP280_MODE_NORMAL,
        .osrs_press = BMP280_OSRS_STANDARD,
        .osrs_temp = BMP280_OSRS_ULTRA_LOW,
        .filter = BMP280_FILTER_X8,
        .standby_time = BMP280_DELAY_250MS
    };
    bmp_init(&bmp_config);
    
    double current_temperature = 0;
    double current_pressure = 0;
    while(1)
    {
        bmp_read_temperature(bmp_config, &current_temperature);
        bmp_read_pressure(bmp_config, &current_pressure);
        ESP_LOGI("sensors", "Current temperature is %fC", current_temperature);
        ESP_LOGI("sensors", "Current pressure is %fPa", current_pressure);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    };
}