// Защита заголовка (Include Guard)
#ifndef CORE_INIT_HEADER_FLAG
#define CORE_INIT_HEADER_FLAG

// Подключение внутренних библиотек фреймворка
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <driver/i2c_master.h>

// Подключение внешних библиотек
#include <led_strip.h>

// Подключение компонентов системы
#include <sysconf.h>
#include <led_matrix.h>

void setup_device(led_strip_handle_t matrix_handle, nvs_handle_t nvs_storage_handle);
#endif