idf_component_register(
    SRCS "driver/led_matrix.c" "driver/aht20.c" "driver/bmp280.c" "core/init.c" "core/effects.c" "core/sensors.c" "main.c"
    INCLUDE_DIRS "core" "driver"
)
