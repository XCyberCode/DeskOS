// Защита заголовка (Include Guard)
#ifndef CORE_EFFECTS_HEADER_FLAG
#define CORE_EFFECTS_HEADER_FLAG

// Подключение внутренних библиотек фреймворка
#include <esp_err.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_timer.h>

// Подключение внешних библиотек
#include <led_strip.h>

// Подключение компонентов системы
#include <led_matrix.h>
#include <sysconf.h>
#include <ui.h>
#include <manager.h>

void effect_hsv_rainbow(struct sys_management_t *sys_manager, bool (*hook_handler)(void));
void effect_linear_hsv_rainbow(struct sys_management_t *sys_manager, bool (*hook_handler)(void));
void effect_bouncing_ball(struct sys_management_t *sys_manager, bool (*hook_handler)(void));
#endif