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
    int16_t temperature_queue[8];
    int16_t current_temperature;
    uint16_t pressure_queue[8];
    uint16_t current_pressure;
    uint8_t data_availability;
} sys_management_t;
#endif