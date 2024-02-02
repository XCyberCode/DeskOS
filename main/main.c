// Include internal libraries
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

// Include external libraries
#include <led_strip.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>

// Global variables
led_strip_handle_t matrix_handle;

void app_main(void) 
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = MCON1_GPIO,
        .max_leds = MATRIX_AREA,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB,
        .led_model = LED_MODEL_WS2812,
        .flags.invert_out = false,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &matrix_handle));
    ESP_ERROR_CHECK(gpio_set_direction(CON1_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CON3_GPIO, GPIO_MODE_INPUT));

    uint8_t line_x = 0;
    while(1)
    {
        if(gpio_get_level(CON1_GPIO) && line_x > 0)
        {
            while(gpio_get_level(CON1_GPIO)){}
            line_x--;   
        }

        if(gpio_get_level(CON3_GPIO) && line_x < 7)
        {
            while(gpio_get_level(CON3_GPIO)){}
            line_x++;
        }

        ESP_ERROR_CHECK(led_matrix_clear(matrix_handle));
        ESP_ERROR_CHECK(led_matrix_draw_v_line(matrix_handle, line_x, 0, 8, 0, 30, 30));
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));
    }
}