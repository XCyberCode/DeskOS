// Include header file
#include <led_matrix.h>

// Include core components
#include <sysconf.h>


// Clear all matrix
void led_matrix_clear(led_strip_handle_t matrix_handle)
{
    led_matrix_fill(matrix_handle, 0, 0, 0);
}

void led_matrix_draw_pixel(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint8_t red, uint8_t green, uint8_t blue )
{
    if(y % 2 == 0)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(
            matrix_handle, (7 - y) * MATRIX_WIDTH + x, 
            red, green, blue
        ));
    }
    else
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(
            matrix_handle, (7 - y) * MATRIX_WIDTH + 7 - x, 
            red, green, blue
        ));
    }
}

void led_matrix_draw_pixel_hsv(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, 
    uint16_t hue, uint8_t saturation, uint8_t brightness
)
{
    if(y % 2 == 0)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel_hsv
        (
            matrix_handle, (7 - y) * MATRIX_WIDTH + x, 
            hue, saturation, brightness
        ));
    }
    else
    {
        ESP_ERROR_CHECK(led_strip_set_pixel_hsv
        (
            matrix_handle, (7 - y) * MATRIX_WIDTH + 7 - x, 
            hue, saturation, brightness
        ));
    }
}

void led_matrix_draw_h_line(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint8_t red, uint8_t green, uint8_t blue
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel(matrix_handle, x + pixel, y, red, green, blue);
    }
}

void led_matrix_draw_v_line(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint8_t red, uint8_t green, uint8_t blue
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel(matrix_handle, x, y + pixel, red, green, blue);
    }
}

void led_matrix_draw_d_line
(
    led_strip_handle_t matrix_handle,
    uint16_t y, uint16_t length,
    bool direction,
    uint8_t red, uint8_t green, uint8_t blue
)
{
    if(direction)
    {
        for(int y_axis = y; y_axis <= y + length - 1; y_axis++)
        {
            led_matrix_draw_pixel(
                matrix_handle, y_axis, y_axis, 
                red, green, blue
            );
        }
    }
    else
    {
        for(int y_axis = y; y_axis >= y - length; y_axis--)
        {
            led_matrix_draw_pixel(
                matrix_handle, y_axis, y_axis, 
                red, green, blue
            );
        }
    }
}

void led_matrix_fill
(
    led_strip_handle_t matrix_handle,
    uint8_t red, uint8_t green, uint8_t blue
)
{
    for(uint16_t current_pixel = 0; current_pixel < MATRIX_AREA; current_pixel++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel
        (
            matrix_handle, current_pixel, 
            red, green, blue
        ));
    }
}

void led_matrix_fill_hsv
(
    led_strip_handle_t matrix_handle,
    uint16_t hue, uint8_t saturation, uint8_t value
)
{
    for(uint16_t current_pixel = 0; current_pixel < MATRIX_AREA; current_pixel++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel_hsv
        (
            matrix_handle, current_pixel, 
            hue, saturation, value
        ));
    }
}

void led_matrix_draw_v_line_hsv
(
    led_strip_handle_t matrix_handle, 
    uint16_t x, uint16_t y, uint16_t length, 
    uint16_t hue, uint8_t saturation, uint8_t brightness 
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel_hsv
        (
            matrix_handle, x, y + pixel, 
            hue, saturation, brightness
        );
    }
}

void led_matrix_draw_h_line_hsv
(
    led_strip_handle_t matrix_handle,        // Matrix handle
    uint16_t x, uint16_t y, uint16_t length, // Line properties
    uint16_t hue, uint8_t saturation, uint8_t brightness 
)
{
    for(int pixel = 0; pixel < length; pixel++)
    {
        led_matrix_draw_pixel_hsv
        (
            matrix_handle, x + pixel, y, 
            hue, saturation, brightness
        );
    }
}

void led_matrix_draw_rect
(
    led_strip_handle_t matrix_handle,
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    uint8_t red, uint8_t green, uint8_t blue
)
{
    led_matrix_draw_v_line(
        matrix_handle, 
        x, y, height, 
        red, green, blue
    );

    led_matrix_draw_v_line(
        matrix_handle, 
        x + width - 1, y, height, 
        red, green, blue
    );

    led_matrix_draw_h_line(
        matrix_handle,
        x, y + height - 1, width,
        red, green, blue
    );

    led_matrix_draw_h_line(
        matrix_handle,
        x, y, width,
        red, green, blue
    );
}


void led_matrix_draw_rect_hsv
(
    led_strip_handle_t matrix_handle,
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    uint16_t hue, uint8_t saturation, uint8_t brightness
)
{
    led_matrix_draw_v_line_hsv(
        matrix_handle, 
        x, y, height, 
        hue, saturation, brightness
    );

    led_matrix_draw_v_line_hsv(
        matrix_handle, 
        x + width - 1, y, height, 
        hue, saturation, brightness
    );

    led_matrix_draw_h_line_hsv(
        matrix_handle,
        x, y + height - 1, width,
        hue, saturation, brightness
    );

    led_matrix_draw_h_line_hsv(
        matrix_handle,
        x, y, width,
        hue, saturation, brightness
    );
}