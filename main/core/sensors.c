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
        .dev_bus_config = &bmp_dev_config,
        .dev_handle = &bmp_handle,
        .type = SENSOR_TYPE_BMP280,
        .mode = BMP280_MODE_NORMAL
    };
    bmp_init(bmp_config);
    while(1);
}