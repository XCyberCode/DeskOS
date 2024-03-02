// Prevent reinclude
#ifndef LIB_BMP280_HEADER_FLAG
#define LIB_BMP280_HEADER_FLAG

// Include core components
#include <driver/i2c.h>

// ================================================
//  Naming of the components:
//  bmp* or bmx* - works on both BMP280 and BME280
//  bme* - works only on BME280
// ================================================

// =======================
//  CONFIGURATION SECTION
// =======================

// Type of the sensor
// BMP280 can measure temperature and pressure
// BME280 can measure temperature, pressure and humidity
// BME680 can measure temperature, pressure, humidity and air quality 
typedef enum 
{
    SENSOR_TYPE_BMP280 = 0,
    SENSOR_TYPE_BME280 = 1
    // SENSOR_TYPE_BME680 = 2
} bmx_sensor_type_t;

// Working mode of the sensor
// Forced - manual measurements (initiated by user)
// Normal - automatic measurements
typedef enum {
    BMP280_MODE_SLEEP = 0,
    BMP280_MODE_FORCED = 1,
    BMP280_MODE_NORMAL = 3
} bmp280_mode_t;

// Pressure oversampling (measurement quality)
typedef enum
{
    BMP280_NO_OVERSAMPLE = 0, // No measurement -_-
    BMP280_ULTRA_LOW = 1,     // Oversampling X1
    BMP280_LOW = 2,           // Oversampling X2
    BMP280_STANDARD = 3,      // Oversampling X4
    BMP280_HIGH = 4,          // Oversampling X8
    BMP280_ULTRA = 5          // Oversampling X16
} bmp280_oversampling_t;

// Data filtering
typedef enum 
{
    BMP280_FILTER_NONE = 0,
    BMP280_FILTER_X1 = 1,
    BMP280_FILTER_X2 = 2,
    BMP280_FILTER_X4 = 3,
    BMP280_FILTER_X8 = 4,
    BMP280_FILTER_X16 = 5
} bmp280_filtering_t;

// Delay between measurements
typedef enum 
{
    BMP280_DELAY_500NS = 0, // 0.5 milliseconds (500 nanoseconds)
    BMP280_DELAY_62MS = 1,  // 62.5 milliseconds
    BMP280_DELAY_125MS = 2, // 125 milliseconds
    BMP280_DELAY_250MS = 3, // 250 milliseconds
    BMP280_DELAY_500MS = 4, // 500 milliseconds
    BMP280_DELAY_1S = 5,    // 1 second
    BMP280_DELAY_2S = 6,    // 2 seconds
    BMP280_DELAY_4S = 7     // 4 seconds
} bmp280_delaying_t;

// Sensor configuration structure
typedef struct {
    i2c_config_t bus_config;            // I2C configuration
    bmx_sensor_type_t type;             // Type of the sensor: BMP280 or BME280
    bmp280_mode_t mode;                 // Working mode of the sensor
    bmp280_filtering_t filter;          // Sensor measurement filtering
    bmp280_oversampling_t oversampling; // Sensor measurement oversampling
    bmp280_delaying_t standby;          // Delay between measurements
} bmx_config_t;

// =================
//  METHODS SECTION 
// =================

// Initialize the sensor
// @param sensor_config structure with sensor configuration
void bmp280_init(bmx_config_t sensor_config);

// Read temperature from the sensor
// @param sensor_config sensor configuration structure
// @param *temperature pointer to the temperature variable
void bmp280_get_temperature(bmx_config_t sensor_config, int16_t *temperature);

// Read pressure from the sensor
// @param sensor_config sensor configuration structure
// @param *pressure pointer to the pressure variable
void bmp280_get_humidity(bmx_config_t sensor_config, uint16_t *pressure);

// Read pressure from the sensor and convert it to the altitude
// @param sensor_config sensor configuration structure
// @param *altitude output pointer to the altitude variable
void bmp280_get_altitude(bmx_config_t sensor_config, uint16_t *altitude);

// Get humidity (bme280 only)
// @param sensor_config sensor configuration structure
// @param *humidity pointer to humidity variable
void bme280_get_humidity(bmx_config_t sensor_config, uint8_t *humidity);
#endif