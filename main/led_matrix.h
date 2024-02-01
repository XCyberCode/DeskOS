// Prevent reinclude
#pragma once

// Color configuration structure
struct color_t;

// Matrix methods
// Clear all pixels of the matrix
void led_matrix_clear();

// Initialize led matrix
void led_matrix_init();

// Draw pixel by position
void led_matrix_draw_pixel();

// Draw horizontal line
void led_matrix_draw_h_line();

// Draw vertical line
void led_matrix_draw_v_line();