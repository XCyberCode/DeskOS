// Include header file
#include <init.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>

void setup_device(led_strip_handle_t matrix_handle, nvs_handle_t nvs_storage_handle)
{
    uint8_t matrix_brightness = 10;

    while(1)
    {
        ESP_ERROR_CHECK(led_matrix_draw_h_line
        (
            matrix_handle, 0, 0, 8, 
            matrix_brightness * 10, matrix_brightness * 10, matrix_brightness * 10
        ));
        ESP_ERROR_CHECK(led_matrix_draw_h_line
        (
            matrix_handle, 0, 7, 8, 
            matrix_brightness * 10, matrix_brightness * 10, matrix_brightness * 10
        ));
        ESP_ERROR_CHECK(led_matrix_draw_v_line
        (
            matrix_handle, 0, 0, 8, 
            matrix_brightness * 10, matrix_brightness * 10, matrix_brightness * 10
        ));
        ESP_ERROR_CHECK(led_matrix_draw_v_line
        (
            matrix_handle, 7, 0, 8, 
            matrix_brightness * 10, matrix_brightness * 10, matrix_brightness * 10
        ));
        ESP_ERROR_CHECK(led_strip_refresh(matrix_handle));

        if(gpio_get_level(CON1_GPIO) && matrix_brightness > 0)
        {
            matrix_brightness--;
            while(gpio_get_level(CON1_GPIO));
        }

        if(gpio_get_level(CON3_GPIO) && matrix_brightness < 25)
        {
            matrix_brightness++;
            while(gpio_get_level(CON3_GPIO));
        }

        if(gpio_get_level(CON2_GPIO))
        {
            while(gpio_get_level(CON2_GPIO));
            break;
        }
    }
    ESP_ERROR_CHECK(nvs_set_i8(nvs_storage_handle, "brightness", matrix_brightness));
    ESP_ERROR_CHECK(nvs_set_i8(nvs_storage_handle, "init_state", 1));
    esp_restart();
}