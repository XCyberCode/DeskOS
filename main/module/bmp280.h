// Prevent reinclude
#ifndef LIB_BMP280_HEADER_FLAG
#define LIB_BMP280_HEADER_FLAG

// Include core components
#include <driver/i2c_master.h>
#include <esp_err.h>
#include <esp_log.h>

// Define registers used in the sensor
#define BMP280_REG_TEMP_XLSB   0xFC // Only 4 bits
#define BMP280_REG_TEMP_LSB    0xFB
#define BMP280_REG_TEMP_MSB    0xFA
#define BMP280_REG_PRESS_XLSB  0xF9 // Only 4 bits
#define BMP280_REG_PRESS_LSB   0xF8
#define BMP280_REG_PRESS_MSB   0xF7
#define BMP280_REG_CONFIG      0xF5 // Bits: t_sb: 7-5, filter: 4-2
#define BMP280_REG_CONTROL     0xF4 // Bits: osrs_t: 7-5, osrs_p: 4-2, mode: 1-0
#define BMP280_REG_STATUS      0xF3 // Bits: measuring: 3, im_update: 0
#define BMP280_REG_RESET       0xE0
#define BMP280_REG_CHIP_ID     0xD0
#define BMP280_REG_CALIBRATE   0x88
#define BMP280_RESET_VALUE     0xB6

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
} bmp_sensor_type_t;

// Working mode of the sensor
// Forced - manual measurements (initiated by user)
// Normal - automatic measurements
typedef enum {
    BMP280_MODE_SLEEP = 0,
    BMP280_MODE_FORCED = 1,
    BMP280_MODE_NORMAL = 3
} bmp_mode_t;

// Pressure oversampling (measurement quality)
typedef enum
{
    BMP280_OSRS_NO_OVERSAMPLE = 0, // No measurement
    BMP280_OSRS_ULTRA_LOW = 1,     // Oversampling X1
    BMP280_OSRS_LOW = 2,           // Oversampling X2
    BMP280_OSRS_STANDARD = 3,      // Oversampling X4
    BMP280_OSRS_HIGH = 4,          // Oversampling X8
    BMP280_OSRS_ULTRA = 5          // Oversampling X16
} bmp_oversampling_t;

// Data filtering
typedef enum 
{
    BMP280_FILTER_NONE = 0,
    BMP280_FILTER_X1 = 1,
    BMP280_FILTER_X2 = 2,
    BMP280_FILTER_X4 = 3,
    BMP280_FILTER_X8 = 4,
    BMP280_FILTER_X16 = 5
} bmp_filtering_t;

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
} bmp_delaying_t;

typedef struct {
    uint16_t T1;
    int16_t T2;
    int16_t T3;
    uint16_t P1;
    int16_t P2;
    int16_t P3;
    int16_t P4;
    int16_t P5;
    int16_t P6;
    int16_t P7;
    int16_t P8;
    int16_t P9;
} bmp_calibration_data_t;

// Structure containing the sensor configuration 
typedef struct {
    i2c_master_dev_handle_t dev_handle;  // Bus device handler
    bmp_sensor_type_t type;              // Type of the sensor: BMP280 or BME280
    bmp_mode_t mode;                  // Working mode of the sensor
    bmp_filtering_t filter;           // Sensor measurement filtering
    bmp_oversampling_t osrs_temp;     // Temperature oversampling
    bmp_oversampling_t osrs_press;    // Pressure oversampling
    bmp_delaying_t standby_time;           // Delay between measurements
    bmp_calibration_data_t calibration_data;
} bmp_config_t;

// =================
//  METHODS SECTION 
// =================

// Internal method. Compensate raw pressure data using formula
// @param sensor_config structure containing the sensor configuration 
// @param raw_pressure raw pressure data
// @param raw_temp raw temperature data (t_fine)
// @param *pressure pointer to the pressure variable
void bmp_compensate_pressure(bmp_config_t sensor_config, int32_t raw_pressure, int32_t raw_temp, double *pressure);

// Internal method. Compensate raw pressure data using formula
// @param sensor_config structure containing the sensor configuration 
// @param raw_temp raw temperature data (t_fine)
// @param *pressure pointer to the pressure variable
void bmp_compensate_temperature(bmp_config_t sensor_config, int32_t raw_temp, int32_t *temperature);

// Internal method. Read compensation values (T1, ..., T3 and P1, ..., P9)
// @param *sensor_config structure containing the sensor configuration
esp_err_t bmp_read_calibration_data(bmp_config_t *sensor_config);

// Initialize the sensor using configuration structure
// @param sensor_config structure containing the sensor configuration 
esp_err_t bmp_init(bmp_config_t *sensor_config);

// Read temperature from the sensor
// @param sensor_config structure containing the sensor configuration 
// @param *temperature pointer to the temperature variable
esp_err_t bmp_read_temperature(bmp_config_t sensor_config, double *temperature);

// Read pressure from the sensor
// @param sensor_config structure containing the sensor configuration 
// @param *pressure pointer to the pressure variable
esp_err_t bmp_read_pressure(bmp_config_t sensor_config, double *pressure);

// Read pressure from the sensor and convert it to the altitude
// @param sensor_config structure containing the sensor configuration 
// @param *altitude output pointer to the altitude variable
esp_err_t bmp_get_altitude(bmp_config_t sensor_config, uint16_t *altitude);

// Get humidity (bme280 only). WIP
// @param sensor_config structure containing the sensor configuration 
// @param *humidity pointer to humidity variable
esp_err_t bmp_read_humidity(bmp_config_t sensor_config, uint8_t *humidity);
#endif