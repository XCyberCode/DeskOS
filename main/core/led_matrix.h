// Prevent reinclude
#pragma once

// Include internal libraries
#include <esp_err.h>

// Include external libaries
#include <led_strip.h>

// Matrix methods
// Clear all pixels of the matrix
esp_err_t led_matrix_draw_v_line(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint8_t red, uint8_t green, uint8_t blue,
    uint8_t brightness
);

esp_err_t led_matrix_draw_h_line(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint8_t red, uint8_t green, uint8_t blue,
    uint8_t brightness
);

esp_err_t led_matrix_draw_pixel(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint8_t red, uint8_t green, uint8_t blue,
    uint8_t brightness
);

esp_err_t led_matrix_clear(led_strip_handle_t matrix_handle);

esp_err_t led_matrix_draw_d_line
(
    led_strip_handle_t matrix_handle,
    uint16_t y, uint16_t length,
    bool direction,
    uint8_t red, uint8_t green, uint8_t blue,
    uint8_t brightness
);