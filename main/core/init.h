// Prevent reinclude
#ifndef CORE_INIT_HEADER_FLAG
#define CORE_INIT_HEADER_FLAG

// Include internal libraries
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>

// Include external libraries
#include <led_strip.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>

void setup_device(led_strip_handle_t matrix_handle, nvs_handle_t nvs_storage_handle);
#endif