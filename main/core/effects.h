// Prevent reinclude
#ifndef CORE_EFFECTS_HEADER_FLAG
#define CORE_EFFECTS_HEADER_FLAG

// Include internal libraries
#include <esp_err.h>

// Include external libraries
#include <led_strip.h>

// Include core componenets
#include <led_matrix.h>
#include <sysconf.h>
#include <ui.h>

void effect_hsv_rainbow(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);
void effect_linear_hsv_rainbow(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);
void effect_bouncing_ball(led_strip_handle_t matrix_handle, uint8_t matrix_brightness);
#endif