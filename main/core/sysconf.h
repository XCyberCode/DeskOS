// Pin number of the left button
#define CON1_GPIO GPIO_NUM_26
// Pin number of the center button
#define CON2_GPIO GPIO_NUM_25
// Pin number of the right button
#define CON3_GPIO GPIO_NUM_27

// Pin number of the matrix connector
#define MCON1_GPIO GPIO_NUM_32
// Width of the matrix
#define MATRIX_WIDTH 8
// Height of the matrix
#define MATRIX_HEIGHT 8
// Area = Height * Width
#define MATRIX_AREA MATRIX_HEIGHT * MATRIX_WIDTH

// Default brightness of the matrix
#define DEFAULT_BRIGHTNESS 1 // From 1 ... 25

// Default startup effect
// Available effects:
// 0 - effect_hsv_rainbow
// 1 - effect_linear_hsv_rainbow
// 2 - effect_bouncing_ball
#define DEFAULT_EFFECT 0

// TODO: Remove and replace
// Number of effects
#define EFFECTS_AMOUNT 3

// === WIP ===
// Enable or disable some effects
#define ENABLE_EFFECT_RAINBOW 1
#define ENABLE_EFFECT_LINEAR_RAINBOW 1
#define ENABLE_EFFECT_BOUNCING_BALL 1

// Climate sensors update delay (milliseconds)
#define SENSORS_UPDATE_DELAY 1000 * 30

// Set sensors address
#define SENSOR_BMPX80_ADDRESS 0x77
#define SENSOR_AHTX0_ADDRESS 0x00

// Configure I2C bus
#define I2C_DEFAULT_SPEED_HZ 100000