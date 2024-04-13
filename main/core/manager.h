// Защита заголовка (Include Guard)
#ifndef CORE_MANAGER_HEADER_FLAG
#define CORE_MANAGER_HEADER_FLAG

// Include external libaries
#include <led_strip.h>

// Подключение компонентов системы
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

// System manipulation strcture
typedef struct sys_management_t
{
    nvs_handle_t nvs_handle;
    led_strip_handle_t matrix_handle;
    int16_t temperature_value;
    uint16_t pressure_value;
} sys_management_t;
#endif