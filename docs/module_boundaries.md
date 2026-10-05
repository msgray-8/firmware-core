# Module Boundary — ADC Conversion

The ADC conversion module converts a raw 12-bit ADC sample into millivolts.

## Public Interface

The public interface is declared in:

`include/adc_conversion.h`

```c
adc_conversion_status_t sample_to_millivolts(
    uint16_t sample,
    uint32_t *millivolts);