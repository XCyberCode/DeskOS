// GPIO configuration

// Left button
#define CON1_GPIO GPIO_NUM_26
// Center button
#define CON2_GPIO GPIO_NUM_25
// Right button
#define CON3_GPIO GPIO_NUM_27

// Matrix parameters
#define MCON1_GPIO GPIO_NUM_32
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8
#define MATRIX_AREA MATRIX_HEIGHT * MATRIX_WIDTH

// System configuration
#define DEFAULT_BRIGHTNESS 1 // From 1 ... 25

// Default effect for first setup
// Available effects:
// 0 - effect_hsv_rainbow
// 1 - effect_linear_hsv_rainbow
// 2 - effect_bouncing_ball
#define DEFAULT_EFFECT 0

// Number of effects
#define EFFECTS_AMOUNT 3

// Deep configuration
#define ESP_ERR_BUTTON_INTERRUPT 0x10E