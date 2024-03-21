#include <ui.h>

void ui_update_task(void *task_parameters)
{
    while(1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void draw_idleview(led_strip_handle_t matrix_handle);
void draw_statview(led_strip_handle_t matrix_handle);
void draw_dataview(led_strip_handle_t matrix_handle);
void draw_overview(led_strip_handle_t matrix_handle);