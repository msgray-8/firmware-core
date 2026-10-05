# Module Boundary — ADC Conversion

The ADC conversion module converts a raw 12-bit ADC sample into millivolts while validating inputs and reporting errors through explicit status codes.

## Public Interface

The public interface is declared in:

`include/adc_conversion.h`

```c
adc_conversion_status_t sample_to_millivolts(
    uint16_t sample,
    uint32_t *millivolts);
```

The caller provides:

- A raw ADC sample.
- A pointer to the variable where the converted millivolt value will be stored.

The function returns a status code describing whether the operation succeeded.

## Module Responsibilities

The ADC conversion module is responsible for:

- Validating the output pointer.
- Validating that the ADC sample is within the valid 12-bit range.
- Converting a valid ADC sample into millivolts.
- Reporting errors through named status codes.

The module does not perform printing, logging, or application-level error handling.

Those responsibilities belong to the caller.

## Module Boundary

```mermaid
flowchart LR
    A[Application / Test Runner]
    H[adc_conversion.h]
    C[adc_conversion.c]

    A -->|includes public interface| H
    C -->|implements declared API| H
    A -->|calls sample_to_millivolts| C
    C -->|status + output value| A
```

## Status Codes

| Status | Meaning |
|---|---|
| `ADC_CONVERSION_OK` | Conversion succeeded |
| `ADC_CONVERSION_INVALID_SAMPLE` | ADC sample is outside the valid range |
| `ADC_CONVERSION_NULL_POINTER` | Output pointer is NULL |

## Valid Input Range

The module assumes a 12-bit ADC:

```text
Minimum sample: 0
Maximum sample: 4095
```

The reference voltage is:

```text
3300 mV
```

The conversion is based on:

```text
millivolts = sample × 3300 / 4095
```

## Design Decisions

### Status-return API

The function returns a status code separately from the converted voltage.

This avoids using a valid numerical result as an error indicator.

### Output Parameter

The converted millivolt value is written through the `millivolts` pointer.

This allows the function return value to be dedicated to reporting success or failure.

### NULL Validation

The output pointer is checked before it is dereferenced.

This prevents the module from intentionally dereferencing a NULL pointer.

### Private Implementation Details

ADC limits and reference-voltage constants remain inside `adc_conversion.c` because callers do not currently need direct access to them.

This keeps the public API small and reduces unnecessary coupling.

## Testing

The host-side test runner currently verifies:

- Minimum valid input.
- Mid-range input.
- Maximum valid input.
- Invalid sample rejection.
- NULL output-pointer rejection.

Tests are built using CMake and executed through CTest.