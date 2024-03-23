// Include header file
#include <setup.h>

void setup_device(led_strip_handle_t matrix_handle, nvs_handle_t nvs_storage_handle)
{
    ESP_ERROR_CHECK(nvs_set_u8(nvs_storage_handle, "init_state", 0));
    uint8_t matrix_brightness = DEFAULT_BRIGHTNESS;
    
    while(1)
    {
        led_matrix_draw_rect(matrix_handle, 0, 0, 8, 8, matrix_brightness * 10, matrix_brightness * 10, matrix_brightness * 10);
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
    ESP_ERROR_CHECK(nvs_set_u8(nvs_storage_handle, "brightness", matrix_brightness));
    ESP_ERROR_CHECK(nvs_set_u8(nvs_storage_handle, "init_state", 1));
    esp_restart();
}