#include <stddef.h>

#include "pointer_utils.h"

pointer_utils_status_t swap_uint32(
    uint32_t *a,
    uint32_t *b)
{
    if ((a == NULL) || (b == NULL))
    {
        return POINTER_UTILS_NULL_POINTER;
    }

    uint32_t temp = *a;
    *a = *b;
    *b = temp;

    return POINTER_UTILS_OK;
}

pointer_utils_status_t sum_samples(
    const uint16_t *samples,
    size_t count,
    uint32_t *sum)
{
    if (sum == NULL)
    {
        return POINTER_UTILS_NULL_POINTER;
    }

    if ((samples == NULL) && (count > 0U))
    {
        return POINTER_UTILS_NULL_POINTER;
    }

    uint32_t total = 0U;

    for (size_t i = 0U; i < count; i++)
    {
        total += samples[i];
    }

    *sum = total;

    return POINTER_UTILS_OK;
}