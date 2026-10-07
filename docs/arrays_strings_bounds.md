# Arrays, Strings, and Bounds

## Array Bounds

For an array with `N` elements, valid indexes are:

```text
0 through N - 1
```

Accessing index `N` is already out of bounds.

For example:

```c
uint16_t samples[4] = {100U, 200U, 300U, 400U};
```

Valid indexes are:

```text
0, 1, 2, 3
```

## Array Decay

When an array is passed to a function, it usually decays into a pointer to its first element.

For example:

```c
void process_samples(
    const uint16_t *samples,
    size_t count);
```

The pointer identifies where the data starts, while `count` tells the function how many elements are valid.

A pointer alone does not retain the original array length.

## sizeof and Arrays

For a real array object:

```c
uint16_t samples[4];
```

the number of elements can be calculated using:

```c
sizeof(samples) / sizeof(samples[0])
```

However, after the array has decayed to a function parameter pointer, `sizeof()` returns the size of the pointer rather than the size of the original array.

## Capacity vs Length

Capacity and length are different concepts.

```text
capacity → total storage available
length   → amount of valid data currently stored
```

For example:

```c
char buffer[16] = "HELLO";
```

has:

```text
capacity = 16 bytes
string length = 5 characters
```

## C String Termination

A valid C string must end with:

```c
'\0'
```

For example:

```c
char text[] = "ABC";
```

is stored as:

```text
'A' 'B' 'C' '\0'
```

A missing terminator can cause string functions to read beyond the valid buffer.

## Bounded Scanning

The tokenizer verifies that a null terminator exists within the provided buffer capacity instead of calling `strlen()` blindly on untrusted input.

If no terminator is found before the end of the buffer, the tokenizer returns:

```c
TOKENIZER_MISSING_TERMINATOR
```

## Tokenizer Design

The tokenizer API is:

```c
tokenizer_status_t tokenize_command(
    char *buffer,
    size_t buffer_capacity,
    char *tokens[],
    size_t max_tokens,
    size_t *token_count);
```

The interface separates:

```text
buffer          → input storage
buffer_capacity → maximum valid memory range
tokens          → output token pointers
max_tokens      → capacity of the token pointer array
token_count     → actual number of tokens found
```

## In-Place Tokenization

The tokenizer modifies the input buffer by replacing spaces with `'\0'`.

For example:

```text
SET LED ON
```

becomes conceptually:

```text
SET\0LED\0ON\0
```

The token array then points into the original buffer:

```text
tokens[0] → "SET"
tokens[1] → "LED"
tokens[2] → "ON"
```

This avoids copying each token into separate storage.

## Boundary and Failure Testing

The tokenizer tests currently cover:

- Normal command parsing
- Empty input
- Multiple spaces
- Leading and trailing spaces
- Too many tokens
- Missing null terminator
- NULL input buffer

These tests are intended to exercise both normal operation and boundary conditions.

## Engineering Rules

When working with buffers and strings:

- Never access an index outside the valid range.
- Keep length and capacity separate.
- Do not assume external data is null-terminated.
- Validate bounds before reading or writing.
- Reserve space for `'\0'` when constructing C strings.
- Pair buffer pointers with explicit size information.