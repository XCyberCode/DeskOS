// Prevent reannounce
#pragma once

// Include external libraries
#include <led_strip.h>
#include <conf.h>

// Configure global variables
led_strip_handle_t led_strip;

void clear_led_strip(led_strip_handle_t strip, uint32_t leds_count)
{
    for(int i = 0; i < leds_count; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(strip, i, 0, 0, 0));
    }
}

void init_led_strip(void) 
{
    // LED strip initialization with the GPIO and pixels number
    led_strip_config_t strip_config = {
        .strip_gpio_num = MCON_GPIO, // The GPIO that connected to the LED strip's data line
        .max_leds = MATRIX_WIDTH * MATRIX_HEIGHT, // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812, // LED strip model
        .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false, // whether to enable the DMA feature
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
}