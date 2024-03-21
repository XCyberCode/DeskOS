idf_component_register(
    SRCS "module/led_matrix.c" "module/aht20.c" "module/bmp280.c" "core/init.c" "core/effects.c" "core/sensors.c" "core/ui.c" "main.c"
    INCLUDE_DIRS "core" "module"
)
