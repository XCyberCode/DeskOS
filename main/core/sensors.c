// Подключение заголовочного файла
#include <sensors.h>

void sensor_write_queue(void *timer_parameters)
{
    struct sys_management_t *sys_manager = timer_parameters;
    
    if(sys_manager->data_availability < 8)
    {
        sys_manager->data_availability++;
    }

    memcpy(
        sys_manager->temperature_queue + 1, 
        sys_manager->temperature_queue,
        (sys_manager->data_availability - 1) * sizeof(sys_manager->temperature_queue[0])
    );
    sys_manager->temperature_queue[0] = sys_manager->current_temperature;

    memcpy(
        sys_manager->pressure_queue + 1,
        sys_manager->pressure_queue,
        (sys_manager->data_availability - 1) * sizeof(sys_manager->pressure_queue[0])
    );
    sys_manager->pressure_queue[0] = sys_manager->current_pressure * 0.0075;

    memcpy(
        sys_manager->forecast_queue + 1,
        sys_manager->forecast_queue,
        (sys_manager->data_availability - 1) * sizeof(sys_manager->forecast_queue[0])
    );
    if(sys_manager->pressure_queue[0] > sys_manager->pressure_queue[1] && sys_manager->current_forecast > -4)
    {
        sys_manager->current_forecast--;
    }
    else if(sys_manager->pressure_queue[0] < sys_manager->pressure_queue[1] && sys_manager->current_forecast < 3)
    {
        sys_manager->current_forecast++;
    }
    sys_manager->forecast_queue[0] = sys_manager->current_forecast;

    ESP_LOGI("sensors", "Measurements queue has been updated.");
    ESP_LOGI("sensors", "New values: T:%.0f, P:%.0f, F:%d", sys_manager->temperature_queue[0], sys_manager->pressure_queue[0], sys_manager->forecast_queue[0]);
    ESP_LOGI("sensors", "Current availability is %d.", sys_manager->data_availability);
}

void sensor_update_task(void *task_parameters)
{
    struct sys_management_t *sys_manager = task_parameters;

    esp_timer_create_args_t sensor_queue_timer = 
    {
        .arg = task_parameters,
        .callback = &sensor_write_queue,
        .name = "sensor_queue"
    };
    esp_timer_handle_t sensor_queue_handle;
    ESP_ERROR_CHECK(esp_timer_create(&sensor_queue_timer, &sensor_queue_handle));

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
        .osrs_press = BMP280_OSRS_ULTRA,
        .osrs_temp = BMP280_OSRS_LOW,
        .filter = BMP280_FILTER_X16,
        .standby_time = BMP280_DELAY_62MS
    };
    bmp_init(&bmp_config);
    
    double current_temperature = 0;
    double current_pressure = 0;

    bmp_read_temperature(bmp_config, &current_temperature);
    sys_manager->current_temperature = current_temperature;
    bmp_read_pressure(bmp_config, &current_pressure);
    sys_manager->current_pressure = current_pressure;
    sensor_write_queue(task_parameters);

    ESP_ERROR_CHECK(esp_timer_start_periodic(sensor_queue_handle, 1000 * 1000 * QUEUE_UPDATE_DELAY));
    while(1)
    {
        bmp_read_temperature(bmp_config, &current_temperature);
        sys_manager->current_temperature = current_temperature;

        bmp_read_pressure(bmp_config, &current_pressure);
        sys_manager->current_pressure = current_pressure;

        vTaskDelay(SENSORS_UPDATE_DELAY / portTICK_PERIOD_MS);
    };
}