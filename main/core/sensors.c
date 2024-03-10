// Include header file
#include <sensors.h>

// Include core libraries
#include <sysconf.h>

void sensor_update_task(void * task_parameters)
{
    i2c_master_bus_config_t i2c_master_bus_config = {
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0
    };
    i2c_master_bus_handle_t i2c_master_bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_bus_config, &i2c_master_bus_handle));

    i2c_device_config_t aht_bus_config = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SENSOR_AHTX0_ADDRESS,
        .scl_speed_hz = I2C_DEFAULT_SPEED_HZ
    };
    ahtx_config_t aht_sensor_config = 
    {
        .dev_bus_config = &aht_bus_config,
        .master_bus_handle = & i2c_master_bus_handle
    };
    ESP_ERROR_CHECK(aht20_init(aht_sensor_config));
}