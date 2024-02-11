// Prevent reinclude
#ifndef AHT20_HEADER_FLAG
#define AHT20_HEADER_FLAG

// Include core components
#include <driver/i2c.h>

void aht20_init(i2c_config_t aht20_config);
void aht20_get_temperature(i2c_config_t aht20_config, int16_t *temperature);
void aht20_get_humidity(i2c_config_t aht20_config, uint8_t *humidity);
#endif