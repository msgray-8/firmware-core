# Structs, Unions, Enums, and Serialization

## Structs

Structures group related data into one typed object.

Example:

```c
typedef struct
{
    uint16_t sensor_id;
    int16_t temperature_centi_c;
    uint32_t timestamp_ms;
} sensor_record_t;
```

This keeps logically related sensor information together.

## Layout, Alignment, and Padding

The compiler decides how structure members are arranged in memory according to the target ABI and alignment rules.

For example:

```c
typedef struct
{
    uint8_t id;
    uint32_t value;
} measurement_t;
```

may require padding between `id` and `value`.

The actual layout should be inspected using:

```c
sizeof(type)
offsetof(type, member)
```

rather than guessed.

## Observed Sensor Record Layout

On the current host toolchain:

```text
sizeof(sensor_record_t) = 8 bytes

sensor_id offset          = 0
temperature_centi_c offset = 2
timestamp_ms offset       = 4
```

This layout is specific to the current compiler, architecture, and ABI.

Code should not assume that another target will necessarily use the same layout.

## Enums

Enums give meaningful names to related integral states or types.

Example:

```c
typedef enum
{
    EVENT_SENSOR = 0,
    EVENT_BUTTON,
    EVENT_ERROR
} event_type_t;
```

This is clearer than using unexplained integer values.

## Unions

Union members share the same storage.

Example:

```c
typedef union
{
    sensor_record_t sensor;
    uint8_t button_id;
    uint32_t error_code;
} event_payload_t;
```

The union must be large enough to hold its largest member.

On the current host:

```text
sizeof(event_payload_t) = 8 bytes
```

because `sensor_record_t` is the largest member.

## Tagged Unions

A tagged union combines an enum with a union.

```c
typedef struct
{
    event_type_t type;
    event_payload_t payload;
} event_t;
```

The `type` field identifies which union member currently contains meaningful data.

For example:

```text
EVENT_SENSOR → payload.sensor
EVENT_BUTTON → payload.button_id
EVENT_ERROR  → payload.error_code
```

The active union member should always agree with the tag.

## Constructor Functions

The event model uses constructor functions such as:

```c
event_make_sensor(...)
event_make_button(...)
event_make_error(...)
```

These functions keep the event type and payload consistent and reduce the chance of constructing invalid tagged events manually.

## Storage Layout Is Not a Wire Format

A structure's in-memory layout must not automatically be treated as a communication or storage format.

Raw structure bytes may depend on:

- padding
- alignment
- endianness
- compiler
- ABI
- enum representation
- target architecture

Therefore code should avoid blindly transmitting:

```c
(uint8_t *)&record
```

with:

```c
sizeof(record)
```

as though that defines a portable protocol.

## Explicit Serialization

The sensor record uses an explicit little-endian wire format:

```text
Bytes 0-1 → sensor_id
Bytes 2-3 → temperature_centi_c
Bytes 4-7 → timestamp_ms
```

The serializer is:

```c
sensor_record_serialize_le(...)
```

This function writes each byte deliberately.

The wire format is therefore independent of the structure's internal memory layout.

## Example Serialized Record

For:

```text
sensor_id = 0x1234
temperature_centi_c = -550
timestamp_ms = 0x12345678
```

the serialized bytes are:

```text
34 12 DA FD 78 56 34 12
```

## Engineering Rules

- Do not assume `sizeof(struct)` equals the sum of member sizes.
- Inspect layout with `sizeof()` and `offsetof()` when layout matters.
- Use enums for meaningful states and event types.
- Use tagged unions so the active union member is explicit.
- Do not depend on implementation-specific union type punning.
- Treat in-memory representation and external serialization as separate concerns.
- Define byte order explicitly for protocols and stored data.