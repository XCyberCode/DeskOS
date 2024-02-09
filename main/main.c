// The Project MATRIXED, 2024

// Include internal libraries
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <nvs.h>
#include <nvs_flash.h>

// Include external libraries
#include <led_strip.h>

// Include core components
#include <sysconf.h>
#include <led_matrix.h>
#include <init.h>
#include <effects.h>

// Global variables
led_strip_handle_t matrix_handle;
nvs_handle_t nvs_storage_handle;

void app_main(void) 
{
    // Prepare variables
    uint8_t current_effect = DEFAULT_EFFECT;
    uint8_t matrix_brightness = DEFAULT_BRIGHTNESS;

    // Configure hardware
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

    // Initialize led matrix
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &matrix_handle));

    // Initialize GPIOS
    ESP_ERROR_CHECK(gpio_set_direction(CON1_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CON2_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(CON3_GPIO, GPIO_MODE_INPUT));

    // Initialize NVS subsystem
    esp_err_t nvs_err = nvs_flash_init();
    if(nvs_err == ESP_ERR_NVS_NO_FREE_PAGES || nvs_err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_err);

    // Open NVS for RW
    ESP_ERROR_CHECK(nvs_open("settings", NVS_READWRITE, &nvs_storage_handle));

    // Check initialization state
    uint8_t device_init_state;
    nvs_err = nvs_get_u8(nvs_storage_handle, "init_state", &device_init_state);
    if(nvs_err == ESP_OK)
    {
        // Check device init state
        if(!device_init_state)
        {
            // Proceed setup
            setup_device(matrix_handle, nvs_storage_handle);
        }
        else
        {
            // Set variables values
            nvs_get_u8(nvs_storage_handle, "brightness", &matrix_brightness);
        }
    }
    // Check NVS entry existance
    else if(nvs_err == ESP_ERR_NVS_NOT_FOUND)
    {
        // Begin setup
        setup_device(matrix_handle, nvs_storage_handle);
    }

    // TODO: Move all of this code to the dedicated file
    while(1)
    {
        if(current_effect == 0)
        {
            effect_hsv_rainbow(matrix_handle, matrix_brightness);
        }
        else if(current_effect == 1)
        {
            effect_linear_hsv_rainbow(matrix_handle, matrix_brightness);
        }
        else if(current_effect == 2)
        {
            effect_bouncing_ball(matrix_handle, matrix_brightness);
        }
        
        while(gpio_get_level(CON2_GPIO));

        if(current_effect < EFFECTS_AMOUNT - 1)
        {
            current_effect++;
        }
        else
        {
            current_effect = 0;
        }
    }
}