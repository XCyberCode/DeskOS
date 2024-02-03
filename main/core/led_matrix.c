// Include header file
#include <led_matrix.h>

// Include core components
#include <sysconf.h>


// Clear all matrix
esp_err_t led_matrix_clear(led_strip_handle_t matrix_handle)
{
    for(int i = 0; i < MATRIX_LENGTH * MATRIX_WIDTH; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(matrix_handle, i, 0, 0, 0));
    }
    return ESP_OK;
}

esp_err_t led_matrix_draw_pixel(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint8_t red, uint8_t green, uint8_t blue)
{
    if(y % 2 == 0)
    {
        ESP_ERROR_CHECK(
            led_strip_set_pixel(
                matrix_handle, y * MATRIX_WIDTH + x, 
                red, green, blue
            )
        );
    }
    else
    {
        ESP_ERROR_CHECK(
            led_strip_set_pixel(
                matrix_handle, y * MATRIX_WIDTH + 7 - x, 
                red, green, blue
            )
        );
    }
    return ESP_OK;
}

esp_err_t led_matrix_draw_h_line(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint8_t red, uint8_t green, uint8_t blue                     // Color of the pixelss
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        ESP_ERROR_CHECK(led_matrix_draw_pixel(matrix_handle, x + pixel, y, red, green, blue));
    }
    return ESP_OK;
}

esp_err_t led_matrix_draw_v_line(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint32_t length, 
    uint8_t red, uint8_t green, uint8_t blue
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        ESP_ERROR_CHECK(led_matrix_draw_pixel(matrix_handle, x, y + pixel, red, green, blue));
    }
    return ESP_OK;
}