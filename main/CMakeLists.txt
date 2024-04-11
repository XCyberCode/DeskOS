idf_component_register(
    SRCS "module/led_matrix.c" "module/aht20.c" "module/bmp280.c" "core/setup.c" "core/effects.c" "core/sensors.c" "core/ui.c" "core/tools.c" "main.c"
    INCLUDE_DIRS "core" "module"
)
