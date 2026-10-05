#include <stddef.h>

#include "adc_conversion.h"

#define ADC_MAX_VALUE 4095U
#define ADC_REFERENCE_MV 3300U

adc_conversion_status_t sample_to_millivolts(
    uint16_t sample,
    uint32_t *millivolts)
{
    if (millivolts == NULL)
    {
        return ADC_CONVERSION_NULL_POINTER;
    }

    if (sample > ADC_MAX_VALUE)
    {
        return ADC_CONVERSION_INVALID_SAMPLE;
    }

    *millivolts =
        (uint32_t)sample * ADC_REFERENCE_MV / ADC_MAX_VALUE;

    return ADC_CONVERSION_OK;
}