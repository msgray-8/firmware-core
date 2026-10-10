#ifndef BITFIELD_H
#define BITFIELD_H

#include <stdint.h>

typedef enum
{
    BITFIELD_OK = 0,
    BITFIELD_NULL_POINTER = -1,
    BITFIELD_INVALID_POSITION = -2,
    BITFIELD_INVALID_WIDTH = -3,
    BITFIELD_VALUE_TOO_LARGE = -4

} bitfield_status_t;

bitfield_status_t field_get_u32(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t *field_value);

bitfield_status_t field_set_u32(
    uint32_t original,
    uint8_t position,
    uint8_t width,
    uint32_t field_value,
    uint32_t *result);

#endif