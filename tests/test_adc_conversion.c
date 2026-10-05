#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "adc_conversion.h"

static int run_test(
    uint16_t sample,
    adc_conversion_status_t expected_status,
    uint32_t expected_mv)
{
    uint32_t millivolts = 0U;

    adc_conversion_status_t status =
        sample_to_millivolts(sample, &millivolts);

    if (status != expected_status)
    {
        printf("FAIL: sample %u returned wrong status\n",
               (unsigned int)sample);

        return 1;
    }

    if ((status == ADC_CONVERSION_OK) &&
        (millivolts != expected_mv))
    {
        printf("FAIL: sample %u expected %u mV, got %u mV\n",
               (unsigned int)sample,
               (unsigned int)expected_mv,
               (unsigned int)millivolts);

        return 1;
    }

    printf("PASS: sample %u\n",
           (unsigned int)sample);

    return 0;
}

static int run_null_pointer_test(void)
{
    adc_conversion_status_t status =
        sample_to_millivolts(2048U, NULL);

    if (status != ADC_CONVERSION_NULL_POINTER)
    {
        printf("FAIL: NULL pointer was not rejected\n");
        return 1;
    }

    printf("PASS: NULL pointer rejected\n");

    return 0;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        0U,
        ADC_CONVERSION_OK,
        0U);

    failures += run_test(
        2048U,
        ADC_CONVERSION_OK,
        1650U);

    failures += run_test(
        4095U,
        ADC_CONVERSION_OK,
        3300U);

    failures += run_test(
        4096U,
        ADC_CONVERSION_INVALID_SAMPLE,
        0U);

    failures += run_null_pointer_test();

    if (failures == 0)
    {
        printf("All tests passed\n");
        return 0;
    }

    printf("%d test(s) failed\n", failures);

    return 1;
}