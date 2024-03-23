// The Project MATRIXED, 2024

// Include internal libraries
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <nvs_flash.h>

// Include external libraries
#include <led_strip.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>
#include <setup.h>
#include <effects.h>
#include <sensors.h>
#include <manager.h>

struct sys_management_t system_management;
nvs_handle_t system_nvs_handle;
led_strip_handle_t system_led_strip_handle;
QueueHandle_t system_temperature_queue;
QueueHandle_t system_pressure_queue;

void app_main(void) 
{
    // Initialize GPIOS
    ESP_ERROR_CHECK(gpio_set_direction(CON1_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CON2_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CON3_GPIO, GPIO_MODE_INPUT));

    system_management.nvs_handle = &system_nvs_handle;
    system_management.matrix_handle = &system_led_strip_handle;
    system_management.temperature_queue = &system_temperature_queue;
    system_management.pressure_queue = &system_pressure_queue;
    system_management.hello_datatype = 1;

    // Initialize NVS subsystem
    esp_err_t nvs_err = nvs_flash_init();
    if(nvs_err == ESP_ERR_NVS_NO_FREE_PAGES || nvs_err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_err);

    // Open NVS for RW
    ESP_ERROR_CHECK(nvs_open("settings", NVS_READWRITE, &system_nvs_handle));

    // Check initialization state
    uint8_t device_init_state;
    nvs_err = nvs_get_u8(system_nvs_handle, "init_state", &device_init_state);
    if(nvs_err == ESP_OK)
    {
        
    }
    // Check NVS entry existance
    else if(nvs_err == ESP_ERR_NVS_NOT_FOUND)
    {
        
    }

    // xTaskCreate(sensor_update_task, "sensors", 2048, (void*)&system_management, 1, NULL);
    xTaskCreate(ui_update_task, "ui", 1024, (void*)&system_management, 1, NULL);
}