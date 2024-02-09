// Prevent reinclude
#pragma once

// Include internal libraries
#include <esp_err.h>

// Include external libraries
#include <led_strip.h>

void effect_hsv_rainbow(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);
void effect_linear_hsv_rainbow(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);
void effect_bouncing_ball(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);