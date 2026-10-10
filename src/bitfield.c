#include <limits.h>
#include <stddef.h>

#include "bitfield.h"

#define UINT32_BIT_COUNT 32U

static bitfield_status_t validate_field(
    uint8_t position,
    uint8_t width)
{
    if (position >= UINT32_BIT_COUNT)
    {
        return BITFIELD_INVALID_POSITION;
    }

    if ((width == 0U) ||
        (width > (UINT32_BIT_COUNT - position)))
    {
        return BITFIELD_INVALID_WIDTH;
    }

    return BITFIELD_OK;
}

static uint32_t make_field_mask(
    uint8_t position,
    uint8_t width)
{
    if (width == UINT32_BIT_COUNT)
    {
        return UINT32_MAX;
    }

    return ((1U << width) - 1U) << position;
}

bitfield_status_t field_get_u32(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t *field_value)
{
    if (field_value == NULL)
    {
        return BITFIELD_NULL_POINTER;
    }

    bitfield_status_t status =
        validate_field(position, width);

    if (status != BITFIELD_OK)
    {
        return status;
    }

    uint32_t mask =
        make_field_mask(position, width);

    *field_value =
        (value & mask) >> position;

    return BITFIELD_OK;
}

bitfield_status_t field_set_u32(
    uint32_t original,
    uint8_t position,
    uint8_t width,
    uint32_t field_value,
    uint32_t *result)
{
    if (result == NULL)
    {
        return BITFIELD_NULL_POINTER;
    }

    bitfield_status_t status =
        validate_field(position, width);

    if (status != BITFIELD_OK)
    {
        return status;
    }

    uint32_t max_field_value;

    if (width == UINT32_BIT_COUNT)
    {
        max_field_value = UINT32_MAX;
    }
    else
    {
        max_field_value =
            (1U << width) - 1U;
    }

    if (field_value > max_field_value)
    {
        return BITFIELD_VALUE_TOO_LARGE;
    }

    uint32_t mask =
        make_field_mask(position, width);

    *result =
        (original & ~mask) |
        ((field_value << position) & mask);

    return BITFIELD_OK;
}