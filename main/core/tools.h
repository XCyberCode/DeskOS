// Prevent reinclude
#ifndef CORE_TOOLS_HEADER_FLAG
#define CORE_TOOLS_HEADER_FLAG

// Include internal libraries
#include <inttypes.h>

int32_t fast_remap(
    int32_t current_value,
    int32_t source_min_value,
    int32_t source_max_value,
    int32_t destination_min_value,
    int32_t destination_max_value
);
#endif