// Защита заголовка (Include Guard)
#ifndef CORE_UI_HEADER_FLAG
#define CORE_UI_HEADER_FLAG

// Подключение внешних библиотек
#include <led_strip.h>

// Подключение внутренних библиотек фреймворка
#include <esp_log.h>
#include <esp_timer.h>

// Подключение компонентов системы
#include <sysconf.h>
#include <effects.h>
#include <manager.h>
#include <tools.h>

typedef struct ui_elements_config_t
{
    bool idleview_enabled;
    bool statview_enabled;
    bool dataview_enabled;
    bool overview_enabled;
} ui_elements_config_t;

void ui_update_task(void *task_parameters);
void draw_idleview(struct sys_management_t *sys_manager);
void draw_statview(struct sys_management_t *sys_manager);
void draw_dataview(struct sys_management_t *sys_manager);
void draw_overview(struct sys_management_t *sys_manager);
#endif