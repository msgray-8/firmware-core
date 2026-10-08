#ifndef EVENT_MODEL_H
#define EVENT_MODEL_H
#define SENSOR_RECORD_WIRE_SIZE 8U

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint16_t sensor_id;
    int16_t temperature_centi_c;
    uint32_t timestamp_ms;
} sensor_record_t;

typedef enum
{
    EVENT_SENSOR = 0,
    EVENT_BUTTON,
    EVENT_ERROR
} event_type_t;

typedef union
{
    sensor_record_t sensor;
    uint8_t button_id;
    uint32_t error_code;
} event_payload_t;

typedef struct
{
    event_type_t type;
    event_payload_t payload;
} event_t;

event_t event_make_sensor(sensor_record_t sensor);
event_t event_make_button(uint8_t button_id);
event_t event_make_error(uint32_t error_code);


typedef enum
{
    EVENT_MODEL_OK = 0,
    EVENT_MODEL_NULL_POINTER = -1,
    EVENT_MODEL_BUFFER_TOO_SMALL = -2
} event_model_status_t;

event_model_status_t sensor_record_serialize_le(
    const sensor_record_t *record,
    uint8_t *output,
    size_t output_capacity);

#endif