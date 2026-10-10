#include <stdint.h>
#include <stdio.h>

#include "bitfield.h"

static int test_get_middle_field(void)
{
    uint32_t field = 0U;

    bitfield_status_t status =
        field_get_u32(
            0xB4U,
            4U,
            3U,
            &field);

    if (status != BITFIELD_OK)
    {
        printf("FAIL: middle field extraction returned error\n");
        return 1;
    }

    if (field != 3U)
    {
        printf("FAIL: expected field 3, got %u\n",
               (unsigned int)field);
        return 1;
    }

    printf("PASS: middle field extraction\n");
    return 0;
}

static int test_set_middle_field(void)
{
    uint32_t result = 0U;

    bitfield_status_t status =
        field_set_u32(
            0x83U,
            4U,
            3U,
            5U,
            &result);

    if (status != BITFIELD_OK)
    {
        printf("FAIL: middle field set returned error\n");
        return 1;
    }

    if (result != 0xD3U)
    {
        printf("FAIL: expected 0xD3, got 0x%X\n",
               (unsigned int)result);
        return 1;
    }

    printf("PASS: middle field set preserves unrelated bits\n");
    return 0;
}

static int test_full_width_field(void)
{
    uint32_t field = 0U;

    bitfield_status_t status =
        field_get_u32(
            0x12345678U,
            0U,
            32U,
            &field);

    if ((status != BITFIELD_OK) ||
        (field != 0x12345678U))
    {
        printf("FAIL: full-width field extraction\n");
        return 1;
    }

    printf("PASS: full-width field extraction\n");
    return 0;
}

static int test_invalid_width_zero(void)
{
    uint32_t field = 0U;

    bitfield_status_t status =
        field_get_u32(
            0U,
            0U,
            0U,
            &field);

    if (status != BITFIELD_INVALID_WIDTH)
    {
        printf("FAIL: zero width not rejected\n");
        return 1;
    }

    printf("PASS: zero width rejected\n");
    return 0;
}

static int test_invalid_position(void)
{
    uint32_t field = 0U;

    bitfield_status_t status =
        field_get_u32(
            0U,
            32U,
            1U,
            &field);

    if (status != BITFIELD_INVALID_POSITION)
    {
        printf("FAIL: invalid position not rejected\n");
        return 1;
    }

    printf("PASS: invalid position rejected\n");
    return 0;
}

static int test_field_exceeds_register(void)
{
    uint32_t field = 0U;

    bitfield_status_t status =
        field_get_u32(
            0U,
            30U,
            4U,
            &field);

    if (status != BITFIELD_INVALID_WIDTH)
    {
        printf("FAIL: oversized field not rejected\n");
        return 1;
    }

    printf("PASS: field beyond bit 31 rejected\n");
    return 0;
}

static int test_value_too_large(void)
{
    uint32_t result = 0U;

    bitfield_status_t status =
        field_set_u32(
            0U,
            4U,
            3U,
            8U,
            &result);

    if (status != BITFIELD_VALUE_TOO_LARGE)
    {
        printf("FAIL: oversized field value not rejected\n");
        return 1;
    }

    printf("PASS: oversized field value rejected\n");
    return 0;
}

static int test_null_output(void)
{
    bitfield_status_t status =
        field_get_u32(
            0U,
            0U,
            1U,
            NULL);

    if (status != BITFIELD_NULL_POINTER)
    {
        printf("FAIL: NULL output pointer not rejected\n");
        return 1;
    }

    printf("PASS: NULL output pointer rejected\n");
    return 0;
}

int main(void)
{
    int failures = 0;

    failures += test_get_middle_field();
    failures += test_set_middle_field();
    failures += test_full_width_field();
    failures += test_invalid_width_zero();
    failures += test_invalid_position();
    failures += test_field_exceeds_register();
    failures += test_value_too_large();
    failures += test_null_output();

    if (failures == 0)
    {
        printf("All bitfield tests passed\n");
        return 0;
    }

    printf("%d bitfield test(s) failed\n", failures);
    return 1;
}