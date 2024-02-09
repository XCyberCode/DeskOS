// Prevent reinclude
#pragma once
// Include external libaries
#include <led_strip.h>

void led_matrix_draw_pixel
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint8_t red, uint8_t green, uint8_t blue 
);
void led_matrix_draw_pixel_hsv(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint16_t hue, uint8_t saturation, uint8_t brightness
);

void led_matrix_fill
(
    led_strip_handle_t matrix_handle,
    uint8_t red, uint8_t green, uint8_t blue
);
void led_matrix_fill_hsv
(
    led_strip_handle_t matrix_handle,
    uint16_t hue, uint8_t saturation, uint8_t value
);

void led_matrix_clear(led_strip_handle_t matrix_handle);

void led_matrix_draw_v_line
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint8_t red, uint8_t green, uint8_t blue  
);
void led_matrix_draw_v_line_hsv
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint16_t hue, uint8_t saturation, uint8_t brightness 
);

void led_matrix_draw_h_line
(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint8_t red, uint8_t green, uint8_t blue 
);
void led_matrix_draw_h_line_hsv
(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint16_t hue, uint8_t saturation, uint8_t brightness 
);

void led_matrix_draw_d_line
(
    led_strip_handle_t matrix_handle,
    uint16_t y, uint16_t length,
    bool direction,
    uint8_t red, uint8_t green, uint8_t blue 
);

void led_matrix_draw_rect
(
    led_strip_handle_t matrix_handle,
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    uint8_t red, uint8_t green, uint8_t blue
);
void led_matrix_draw_rect_hsv
(
    led_strip_handle_t matrix_handle,
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    uint16_t hue, uint8_t saturation, uint8_t brightness
);