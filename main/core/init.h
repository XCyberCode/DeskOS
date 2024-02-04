// Prevent reinclude
#pragma once

// Include internal libraries
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>

// Include external libraries
#include <led_strip.h>

esp_err_t setup_device(led_strip_handle_t matrix_handle, nvs_handle_t nvs_storage_handle);