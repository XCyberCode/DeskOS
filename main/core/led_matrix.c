// Include header file
#include "led_matrix.h"

// Include extenal libraries
#include <led_strip.h>

// Include core components
#include "sysconf.h"

// Configure global variables
led_strip_handle_t led_matrix;

// Color configuration structure
struct color_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// Initialize matrix
void led_matrix_init(void)
{
    // LED strip initialization with the GPIO and pixels number
    led_strip_config_t strip_config = {
        .strip_gpio_num = MCON1_GPIO, // The GPIO that connected to the LED strip's data line
        .max_leds = MATRIX_WIDTH * MATRIX_LENGTH, // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812, // LED strip model
        .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false, // whether to enable the DMA feature
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_matrix));
}

// Clear all matrix
void led_matrix_clear()
{
    for(int i = 0; i < MATRIX_LENGTH * MATRIX_WIDTH; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_matrix, i, 0, 0, 0));
    }
}

void led_matrix_draw_pixel(int x, int y, struct color_t color)
{
    if(y % 2 == 0)
    {
        led_strip_set_pixel(
            led_matrix, (y - 1) * MATRIX_WIDTH + x, 
            color.red, color.green, color.blue
        );
    }
    else
    {
        led_strip_set_pixel(
            led_matrix, y * MATRIX_WIDTH - x, 
            color.red, color.green, color.blue
        );
    }
}

void led_matrix_draw_h_line(uint32_t x, uint32_t y, uint32_t length, struct color_t color)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel(x + pixel, y, color);
    }
}

void led_matrix_draw_v_line(uint32_t x, uint32_t y, uint32_t length, struct color_t color)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel(x, y + pixel, color);
    }
}