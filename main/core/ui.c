// Подключение заголовочного файла
#include <ui.h>

void draw_idleview(struct sys_management_t *sys_manager)
{

}
void draw_statview(struct sys_management_t *sys_manager);
void draw_dataview(struct sys_management_t *sys_manager)
{
    led_matrix_clear(sys_manager->matrix_handle);
    for(int item = 0; item < sys_manager->data_availability; item++)
    {
        if(sys_manager->current_dataview_chart == 0)
        {
            led_matrix_draw_v_line(sys_manager->matrix_handle, item, 0, fast_remap(sys_manager->temperature_queue[item], 16, 32, 1, 8), 50, 0, 0);
        }
        else if(sys_manager->current_dataview_chart == 1)
        {
            led_matrix_draw_v_line(sys_manager->matrix_handle, item, 0, fast_remap(sys_manager->pressure_queue[item], 740, 780, 1, 8), 40, 0, 40);
        }
    }
    ESP_ERROR_CHECK(led_strip_refresh(sys_manager->matrix_handle));
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
        draw_dataview(sys_manager);
        if(gpio_get_level(CENTER_BTN_GPIO))
        {
            if(sys_manager->current_dataview_chart < 1)
            {
                sys_manager->current_dataview_chart++;
            }
            else 
            {
                sys_manager->current_dataview_chart = 0;
            }
            while(gpio_get_level(CENTER_BTN_GPIO));
        }
    }
}