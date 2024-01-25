#include <led_strip.h>
#include <freertos/task.h>

void clear_led_strip(led_strip_handle_t strip, uint32_t leds_count)
{
    for(int i = 0; i < leds_count; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(strip, i, 0, 0, 0));
    }
}

void app_main(void) 
{
    led_strip_handle_t led_strip;
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_NUM_27, // The GPIO that connected to the LED strip's data line
        .max_leds = 64, // The number of LEDs in the strip,
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
    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 32, 0, 255, 0));
    ESP_ERROR_CHECK(led_strip_refresh(led_strip));
}