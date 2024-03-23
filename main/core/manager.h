// Prevent reinclude
#ifndef CORE_MANAGER_HEADER_FLAG
#define CORE_MANAGER_HEADER_FLAG

// Include external libaries
#include <led_strip.h>

// Include core components
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

// System manipulation strcture
typedef struct sys_management_t
{
    nvs_handle_t * nvs_handle;
    led_strip_handle_t * matrix_handle;
    QueueHandle_t * temperature_queue;
    QueueHandle_t * pressure_queue;
    uint8_t hello_datatype;
} sys_management_t;
#endif