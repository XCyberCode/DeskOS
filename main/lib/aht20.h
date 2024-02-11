// Prevent reinclude
#ifndef AHT20_HEADER_FLAG
#define AHT20_HEADER_FLAG

// Include core components
#include <driver/i2c.h>

void aht20_init(i2c_config_t i2c_config);
#endif