#ifndef ADC_CONVERSION_H
#define ADC_CONVERSION_H

#include <stdint.h>

typedef enum
{
    ADC_CONVERSION_OK = 0,
    ADC_CONVERSION_INVALID_SAMPLE = -1,
    ADC_CONVERSION_NULL_POINTER = -2

} adc_conversion_status_t;

adc_conversion_status_t sample_to_millivolts(
    uint16_t sample,
    uint32_t *millivolts);

#endif