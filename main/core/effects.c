// Inlcude header file
#include <effects.h>

// Include internal libraries
#include <esp_err.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_timer.h>

// Include external libraries
#include <led_strip.h>

// Include core componenets
#include <led_matrix.h>
#include <sysconf.h>

uint32_t timer_buffer = 0;

void effect_hsv_rainbow(led_strip_handle_t matrix_handle)
{
    uint16_t hue_value = 0;
    while(1)
    {
        if(hue_value < 359)
        {
            hue_value++;
        }
        else
        {
            hue_value = 0;
        }
        ESP_ERROR_CHECK(led_matrix_fill_hsv(matrix_handle, hue_value, 255, 30));
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));

        timer_buffer = esp_timer_get_time();
        while(esp_timer_get_time() < timer_buffer + 50 * 1000)
        {
            if(gpio_get_level(CON2_GPIO))
            {
                return;
            }
        };
    }
}

void effect_linear_hsv_rainbow(led_strip_handle_t matrix_handle)
{
    while(1)
    {
        /* if(hue_value < 360 - MATRIX_WIDTH * 4)
        {
            hue_value++;
        }
        else
        {
            hue_value = 0;
        }

        ESP_ERROR_CHECK(led_matrix_clear(matrix_handle));
        for(int current_line = 0; current_line < MATRIX_WIDTH; current_line++)
        {
            led_matrix_draw_v_line_hsv(matrix_handle, current_line, 0, MATRIX_HEIGHT, hue_value + current_line * 4, 255, 30);
        }
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));

        timer_buffer = esp_timer_get_time();
        while(esp_timer_get_time() < timer_buffer + 50 * 1000)
        {
            if(gpio_get_level(CON2_GPIO))
            {
                return;
            }
        }; */

        for(int hue_value = 0; hue_value < 360 - MATRIX_WIDTH * 4; hue_value++)
        {
            ESP_ERROR_CHECK(led_matrix_clear(matrix_handle));
            for(int current_line = 0; current_line < MATRIX_WIDTH; current_line++)
            {
                led_matrix_draw_v_line_hsv(matrix_handle, current_line, 0, MATRIX_HEIGHT, hue_value + current_line * 4, 255, 30);
            }
            ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));

            timer_buffer = esp_timer_get_time();
            while(esp_timer_get_time() < timer_buffer + 50 * 1000)
            {
                if(gpio_get_level(CON2_GPIO))
                {
                    return;
                }
            };
        }
    }
}

void effect_bouncing_ball(led_strip_handle_t matrix_handle)
{
    uint8_t ball_x = 4;
    uint8_t ball_y = 7;
    int8_t ball_vector_x = 1;
    int8_t ball_vector_y = 1;
    uint16_t hue_value = 0;

    while(1)
    {
        if(ball_x + ball_vector_x == MATRIX_WIDTH || ball_x + ball_vector_x < 0)
        {
            ball_vector_x = -ball_vector_x;
        }

        if(ball_y + ball_vector_y == MATRIX_HEIGHT || ball_y + ball_vector_y < 0)
        {
            ball_vector_y = -ball_vector_y;
        }

        if(hue_value < 359)
        {
            hue_value++;
        }
        else
        {
            hue_value = 0;
        }

        ball_x += ball_vector_x;
        ball_y += ball_vector_y;

        ESP_ERROR_CHECK(led_matrix_clear(matrix_handle));
        ESP_ERROR_CHECK(led_matrix_draw_pixel_hsv(matrix_handle, ball_x, ball_y, hue_value, 255, 30));
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));

        timer_buffer = esp_timer_get_time();
        while(esp_timer_get_time() < timer_buffer + 250 * 1000)
        {
            if(gpio_get_level(CON2_GPIO))
            {
                return;
            }
        };
    }
}