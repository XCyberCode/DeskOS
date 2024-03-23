#ifndef CORE_UI_HEADER_FLAG
#define CORE_UI_HEADER_FLAG

// Include external libraries
#include <led_strip.h>

// Include internal libraries
#include <esp_log.h>

// Include core components
#include <sysconf.h>
#include <effects.h>
#include <manager.h>

typedef struct ui_elements_config_t
{
    bool idleview_enabled;
    bool statview_enabled;
    bool dataview_enabled;
    bool overview_enabled;
} ui_elements_config_t;

void ui_update_task(void *task_parameters);
void draw_idleview(led_strip_handle_t matrix_handle);
void draw_statview(led_strip_handle_t matrix_handle);
void draw_dataview(led_strip_handle_t matrix_handle);
void draw_overview(led_strip_handle_t matrix_handle);
#endif