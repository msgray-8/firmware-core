#ifndef POINTER_UTILS_H
#define POINTER_UTILS_H

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    POINTER_UTILS_OK = 0,
    POINTER_UTILS_NULL_POINTER = -1

} pointer_utils_status_t;

pointer_utils_status_t swap_uint32(
    uint32_t *a,
    uint32_t *b);

pointer_utils_status_t sum_samples(
    const uint16_t *samples,
    size_t count,
    uint32_t *sum);

#endif