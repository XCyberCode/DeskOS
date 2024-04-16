// The Project MATRIXED, 2024

// Include internal libraries
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

// Include external libraries
#include <led_strip.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>
#include <setup.h>
#include <effects.h>
#include <sensors.h>
#include <manager.h>
#include <esp_timer.h>

struct sys_management_t sys_manager;

void app_main(void) 
{
    // Initialize GPIOS
    ESP_ERROR_CHECK(gpio_set_direction(LEFT_BTN_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CENTER_BTN_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(RIGHT_BTN_GPIO, GPIO_MODE_INPUT));

    sys_manager.data_availability = 0;
    sys_manager.current_dataview_chart = 0;
    sys_manager.current_forecast = 0;

    xTaskCreate(sensor_update_task, "sensors", 4096, (void*)&sys_manager, 1, NULL);
    xTaskCreate(ui_update_task, "ui", 4096, (void*)&sys_manager, 1, NULL);
}