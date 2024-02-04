// Prevent reinclude
#pragma once

// Include internal libraries
#include <esp_err.h>

// Include external libraries
#include <led_strip.h>

esp_err_t effect_hsv_rainbow(led_strip_handle_t matrix_handle);