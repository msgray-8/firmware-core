# Bitwise Operations and Register-Style Field Handling

## Core Bit Operations

Bitwise operators manipulate individual bits inside integer values.

### Set a Bit

```c
value |= (1U << bit);
```

This sets the selected bit to `1` while preserving unrelated bits.

### Clear a Bit

```c
value &= ~(1U << bit);
```

This clears the selected bit to `0` while preserving unrelated bits.

### Toggle a Bit

```c
value ^= (1U << bit);
```

This flips the selected bit.

### Test a Bit

```c
if ((value & (1U << bit)) != 0U)
{
    /* bit is set */
}
```

The mask isolates the selected bit.

## Masks and Fields

A mask identifies the exact bits that belong to a field.

For a field starting at bit position `4` with width `3`:

```text
position = 4
width = 3
mask = 0x70
```

In binary:

```text
0111 0000
```

## Field Extraction

A field can be extracted using:

```c
field = (value & mask) >> position;
```

Example:

```text
value = 1011 0100
mask  = 0111 0000
```

After masking:

```text
0011 0000
```

After shifting right by four:

```text
0000 0011
```

So the extracted field value is:

```text
3
```

## Field Setting

To modify only one field while preserving unrelated bits:

```c
result =
    (original & ~mask) |
    ((field_value << position) & mask);
```

The first part:

```c
original & ~mask
```

clears the existing field.

The second part:

```c
(field_value << position) & mask
```

places the new field value into the correct bit positions.

The two parts are combined using bitwise OR.

## Bitfield Module

The public API includes:

```c
bitfield_status_t field_get_u32(
    uint32_t value,
    uint8_t position,
    uint8_t width,
    uint32_t *field_value);
```

and:

```c
bitfield_status_t field_set_u32(
    uint32_t original,
    uint8_t position,
    uint8_t width,
    uint32_t field_value,
    uint32_t *result);
```

These helpers operate on `uint32_t` values and return explicit status codes for invalid operations.

## Validation Rules

For a `uint32_t`, valid bit positions are:

```text
0 through 31
```

A field is valid when:

```text
width > 0
position < 32
width <= 32 - position
```

For example:

```text
position = 30
width = 4
```

is invalid because it would require bits beyond bit 31.

## Full-Width Field

A field with:

```text
position = 0
width = 32
```

is valid because it covers the entire `uint32_t`.

However, this expression must not be used:

```c
1U << 32U
```

because shifting by the width of the operand is undefined behavior.

The implementation therefore handles full-width fields separately using:

```c
UINT32_MAX
```

## Field Value Range

A field of width `N` can store values from:

```text
0 through 2^N - 1
```

For example:

```text
width = 3
valid values = 0 through 7
```

Trying to store `8` in a 3-bit field is rejected with:

```c
BITFIELD_VALUE_TOO_LARGE
```

## Unsigned Arithmetic

Bit manipulation is performed using unsigned fixed-width integer types such as:

```c
uint32_t
```

Unsigned types avoid many of the implementation-defined or undefined behaviors associated with signed shifting.

Masks are created using unsigned literals such as:

```c
1U
```

## Register-Like Behavior

The bitfield helpers are designed to model register manipulation while remaining host-testable.

For example:

```text
original = 0x83
field position = 4
field width = 3
new field value = 5
```

produces:

```text
result = 0xD3
```

Only bits 4 through 6 change.

All unrelated bits remain unchanged.

## GDB Inspection

GDB was used to inspect register-like values in hexadecimal:

```gdb
print/x original
print/x result
```

For the field-setting test:

```text
original = 0x83
result   = 0xD3
```

This verified the read-modify-write behavior directly.

## Boundary Tests

The current bitfield tests cover:

- Middle-field extraction
- Middle-field setting
- Preservation of unrelated bits
- Full-width 32-bit extraction
- Zero-width rejection
- Invalid bit position
- Field extending beyond bit 31
- Field value too large
- NULL output pointer

## Engineering Rules

- Use unsigned fixed-width types for bit manipulation.
- Validate bit positions and field widths before shifting.
- Never shift by a count equal to or greater than the operand width.
- Preserve unrelated bits during field updates.
- Use named masks and positions in real register-level code.
- Treat register manipulation as a read-modify-write operation.
- Prefer explicit masks and shifts over implementation-dependent C bit-fields for portable low-level code.