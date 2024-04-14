// Подключение заголовочного файла
#include <ui.h>

void draw_idleview(struct sys_management_t *sys_manager)
{

}
void draw_statview(struct sys_management_t *sys_manager);
void draw_dataview(struct sys_management_t *sys_manager)
{
    
}
void draw_overview(struct sys_management_t *sys_manager);

void ui_update_task(void *task_parameters)
{
    struct sys_management_t *sys_manager = task_parameters;
    uint8_t current_uiw = 0;
    
    // Настройка параметров светодиодной матрицы
    led_strip_config_t strip_config = {
        .strip_gpio_num = MCON1_GPIO,
        .max_leds = MATRIX_AREA,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,
        .led_model = LED_MODEL_WS2812,
        .flags.invert_out = false,
    };

    // Конфигурация шины передачи данных матрицы
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };

    // Инициализация светодиодной матрицы
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &sys_manager->matrix_handle));
    ESP_LOGI("ui", "Starting is completed.");

    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}