#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "pointer_utils.h"

static int test_swap_valid(void)
{
    uint32_t a = 10U;
    uint32_t b = 20U;

    pointer_utils_status_t status =
        swap_uint32(&a, &b);

    if (status != POINTER_UTILS_OK)
    {
        printf("FAIL: swap returned wrong status\n");
        return 1;
    }

    if ((a != 20U) || (b != 10U))
    {
        printf("FAIL: swap produced wrong values\n");
        return 1;
    }

    printf("PASS: valid swap\n");
    return 0;
}

static int test_swap_null(void)
{
    uint32_t value = 10U;

    pointer_utils_status_t status =
        swap_uint32(NULL, &value);

    if (status != POINTER_UTILS_NULL_POINTER)
    {
        printf("FAIL: NULL swap pointer was not rejected\n");
        return 1;
    }

    printf("PASS: NULL swap pointer rejected\n");
    return 0;
}

static int test_sum_valid(void)
{
    const uint16_t samples[] =
    {
        100U,
        200U,
        300U,
        400U
    };

    uint32_t sum = 0U;

    pointer_utils_status_t status =
        sum_samples(samples, 4U, &sum);

    if (status != POINTER_UTILS_OK)
    {
        printf("FAIL: sum returned wrong status\n");
        return 1;
    }

    if (sum != 1000U)
    {
        printf("FAIL: expected sum 1000, got %u\n",
               (unsigned int)sum);
        return 1;
    }

    printf("PASS: valid sample sum\n");
    return 0;
}

static int test_sum_zero_length(void)
{
    uint32_t sum = 123U;

    pointer_utils_status_t status =
        sum_samples(NULL, 0U, &sum);

    if (status != POINTER_UTILS_OK)
    {
        printf("FAIL: zero-length input returned error\n");
        return 1;
    }

    if (sum != 0U)
    {
        printf("FAIL: zero-length sum was not zero\n");
        return 1;
    }

    printf("PASS: zero-length input\n");
    return 0;
}

static int test_sum_null_output(void)
{
    const uint16_t samples[] = {100U, 200U};

    pointer_utils_status_t status =
        sum_samples(samples, 2U, NULL);

    if (status != POINTER_UTILS_NULL_POINTER)
    {
        printf("FAIL: NULL output pointer was not rejected\n");
        return 1;
    }

    printf("PASS: NULL sum output rejected\n");
    return 0;
}

static int test_sum_null_input(void)
{
    uint32_t sum = 0U;

    pointer_utils_status_t status =
        sum_samples(NULL, 2U, &sum);

    if (status != POINTER_UTILS_NULL_POINTER)
    {
        printf("FAIL: NULL sample buffer was not rejected\n");
        return 1;
    }

    printf("PASS: NULL sample buffer rejected\n");
    return 0;
}
int main(void)
{
    int failures = 0;
    failures += test_sum_null_input();
    failures += test_swap_valid();
    failures += test_swap_null();
    failures += test_sum_valid();
    failures += test_sum_zero_length();
    failures += test_sum_null_output();

    if (failures == 0)
    {
        printf("All pointer utility tests passed\n");
        return 0;
    }

    printf("%d test(s) failed\n", failures);
    return 1;
}