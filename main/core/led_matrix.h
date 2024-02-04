// Prevent reinclude
#pragma once

// Include internal libraries
#include <esp_err.h>

// Include external libaries
#include <led_strip.h>

// Matrix methods

// Draw a vertical line
// @param matrix_handle handler of the matrix
// @param x horizontal position
// @param y vertical position
// @param length length of the line 
// @param red red color
// @param green green color
// @param blue blue color
esp_err_t led_matrix_draw_v_line
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint8_t red, uint8_t green, uint8_t blue  
);

esp_err_t led_matrix_draw_h_line
(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint8_t red, uint8_t green, uint8_t blue 
);

esp_err_t led_matrix_draw_v_line_hsv
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint16_t hue, uint8_t saturation, uint8_t brightness 
);

esp_err_t led_matrix_draw_h_line_hsv
(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint16_t hue, uint8_t saturation, uint8_t brightness 
);

esp_err_t led_matrix_draw_pixel
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint8_t red, uint8_t green, uint8_t blue 
);

esp_err_t led_matrix_clear(led_strip_handle_t matrix_handle);

esp_err_t led_matrix_fill
(
    led_strip_handle_t matrix_handle,
    uint8_t red, uint8_t green, uint8_t blue
);

esp_err_t led_matrix_fill_hsv
(
    led_strip_handle_t matrix_handle,
    uint16_t hue, uint8_t saturation, uint8_t value
);

esp_err_t led_matrix_draw_d_line
(
    led_strip_handle_t matrix_handle,
    uint16_t y, uint16_t length,
    bool direction,
    uint8_t red, uint8_t green, uint8_t blue 
);

esp_err_t led_matrix_draw_pixel_hsv(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint16_t hue, uint8_t saturation, uint8_t brightness
);