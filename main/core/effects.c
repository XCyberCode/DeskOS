// Inlcude header file
#include <effects.h>

// Include internal libraries
#include <esp_err.h>
#include <freertos/task.h>

// Include external libraries
#include <led_strip.h>

// Include core componenets
#include <led_matrix.h>
#include <sysconf.h>

esp_err_t effect_hsv_rainbow(led_strip_handle_t matrix_handle)
{
    uint16_t hue_value = 0;
    while(1)
    {
        if(hue_value < 360)
        {
            hue_value++;
        }
        else
        {
            hue_value = 0;
        }
        ESP_ERROR_CHECK(led_strip_set_pixel_hsv(matrix_handle, 0, hue_value, 255, 30));
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}