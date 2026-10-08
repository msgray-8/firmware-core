#include "event_model.h"

event_t event_make_sensor(sensor_record_t sensor)
{
    event_t event = {0};

    event.type = EVENT_SENSOR;
    event.payload.sensor = sensor;

    return event;
}

event_t event_make_button(uint8_t button_id)
{
    event_t event = {0};

    event.type = EVENT_BUTTON;
    event.payload.button_id = button_id;

    return event;
}

event_t event_make_error(uint32_t error_code)
{
    event_t event = {0};

    event.type = EVENT_ERROR;
    event.payload.error_code = error_code;

    return event;
}

event_model_status_t sensor_record_serialize_le(
    const sensor_record_t *record,
    uint8_t *output,
    size_t output_capacity)
{
    if ((record == NULL) || (output == NULL))
    {
        return EVENT_MODEL_NULL_POINTER;
    }

    if (output_capacity < SENSOR_RECORD_WIRE_SIZE)
    {
        return EVENT_MODEL_BUFFER_TOO_SMALL;
    }

    uint16_t temperature =
        (uint16_t)record->temperature_centi_c;

    output[0] = (uint8_t)(record->sensor_id & 0xFFU);
    output[1] = (uint8_t)((record->sensor_id >> 8U) & 0xFFU);

    output[2] = (uint8_t)(temperature & 0xFFU);
    output[3] = (uint8_t)((temperature >> 8U) & 0xFFU);

    output[4] = (uint8_t)(record->timestamp_ms & 0xFFU);
    output[5] = (uint8_t)((record->timestamp_ms >> 8U) & 0xFFU);
    output[6] = (uint8_t)((record->timestamp_ms >> 16U) & 0xFFU);
    output[7] = (uint8_t)((record->timestamp_ms >> 24U) & 0xFFU);

    return EVENT_MODEL_OK;
}