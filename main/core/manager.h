// Защита заголовка (Include Guard)
#ifndef CORE_MANAGER_HEADER_FLAG
#define CORE_MANAGER_HEADER_FLAG

// Подключение внешних библиотек
#include <led_strip.h>

// Подключение компонентов системы
#include <freertos/FreeRTOS.h>

// Структура для хранения необходимых системе данных
typedef struct sys_management_t
{
    led_strip_handle_t matrix_handle;
    float temperature_queue[8];
    float current_temperature;
    float pressure_queue[8];
    float current_pressure;
    uint8_t data_availability;
    uint8_t current_dataview_chart;
} sys_management_t;
#endif