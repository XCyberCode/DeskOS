// Подключение заголовочного файла
#include <tools.h>

int32_t fast_remap
(
    int32_t current_value,
    int32_t source_min_value,
    int32_t source_max_value,
    int32_t destination_min_value,
    int32_t destination_max_value
)
{
    return (current_value - source_min_value) * (destination_max_value - destination_min_value) / (source_max_value - source_min_value) + destination_min_value;
}