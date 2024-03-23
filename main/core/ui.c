// Include header file
#include <ui.h>

void ui_update_task(void *task_parameters)
{
    struct sys_management_t *sys_manager = task_parameters;
    
    // Configure hardware
    led_strip_config_t strip_config = {
        .strip_gpio_num = MCON1_GPIO,
        .max_leds = MATRIX_AREA,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,
        .led_model = LED_MODEL_WS2812,
        .flags.invert_out = false,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };

    // Initialize led matrix
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, sys_manager->matrix_handle));
    ESP_LOGI("ui", "Starting is complete");

    while(1)
    {
        led_matrix_fill(*(sys_manager->matrix_handle), 255, 0, 0);
        ESP_ERROR_CHECK(led_strip_refresh(*(sys_manager->matrix_handle)));
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void draw_idleview(led_strip_handle_t matrix_handle);

void draw_statview(led_strip_handle_t matrix_handle);

void draw_dataview(led_strip_handle_t matrix_handle);

void draw_overview(led_strip_handle_t matrix_handle);