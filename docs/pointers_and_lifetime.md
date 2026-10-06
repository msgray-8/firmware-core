# Pointers and Lifetime

## Key Concepts

A pointer stores the address of another object.

```c
uint32_t value = 100U;
uint32_t *ptr = &value;
```

In this example:

- `ptr` stores the address of `value`.
- `*ptr` accesses the value stored at that address.
- Writing through `*ptr` modifies the original object.

## Ownership and Borrowing

Functions often receive pointers to objects owned by the caller.

```c
swap_uint32(&a, &b);
```

The caller owns `a` and `b`. The function temporarily borrows their addresses and modifies the original objects.

## Lifetime

A pointer is only useful while the object it points to is still alive.

Returning the address of a normal local variable is invalid:

```c
uint32_t *bad_function(void)
{
    uint32_t value = 25U;
    return &value;
}
```

`value` stops existing when the function returns, so the returned pointer becomes dangling.

## Defensive Pointer Handling

Public APIs should validate pointers before dereferencing them.

```c
if (ptr == NULL)
{
    return POINTER_UTILS_NULL_POINTER;
}
```

A non-NULL pointer is not automatically guaranteed to be valid, but NULL checking prevents one common failure mode.

## Pointer + Length APIs

A pointer alone does not contain information about how many elements are valid.

For buffers and arrays, use a pointer together with a count:

```c
pointer_utils_status_t sum_samples(
    const uint16_t *samples,
    size_t count,
    uint32_t *sum);
```

This pattern is commonly used for:

- UART buffers
- SPI transfers
- ADC sample blocks
- protocol packets
- DMA buffers

## const Correctness

Read-only input data should be exposed through a pointer to const data:

```c
const uint16_t *samples
```

This communicates that the function reads the buffer but does not modify it.

## Debugging

GDB was used to inspect:

```text
a
*a
b
*b
temp
```

This confirmed that pointer variables store addresses while dereferencing accesses the caller's actual values.