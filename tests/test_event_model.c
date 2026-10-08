#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "event_model.h"

static int test_sensor_event(void)
{
    sensor_record_t sensor =
    {
        .sensor_id = 7U,
        .temperature_centi_c = 2534,
        .timestamp_ms = 1000U
    };

    event_t event = event_make_sensor(sensor);

    if (event.type != EVENT_SENSOR)
    {
        printf("FAIL: sensor event has wrong type\n");
        return 1;
    }

    if ((event.payload.sensor.sensor_id != 7U) ||
        (event.payload.sensor.temperature_centi_c != 2534) ||
        (event.payload.sensor.timestamp_ms != 1000U))
    {
        printf("FAIL: sensor event payload incorrect\n");
        return 1;
    }

    printf("PASS: sensor event\n");
    return 0;
}

static int test_button_event(void)
{
    event_t event = event_make_button(3U);

    if (event.type != EVENT_BUTTON)
    {
        printf("FAIL: button event has wrong type\n");
        return 1;
    }

    if (event.payload.button_id != 3U)
    {
        printf("FAIL: button payload incorrect\n");
        return 1;
    }

    printf("PASS: button event\n");
    return 0;
}

static int test_error_event(void)
{
    event_t event = event_make_error(42U);

    if (event.type != EVENT_ERROR)
    {
        printf("FAIL: error event has wrong type\n");
        return 1;
    }

    if (event.payload.error_code != 42U)
    {
        printf("FAIL: error payload incorrect\n");
        return 1;
    }

    printf("PASS: error event\n");
    return 0;
}

static void print_layout(void)
{
    printf("sensor_record_t size: %zu bytes\n",
           sizeof(sensor_record_t));

    printf("sensor_id offset: %zu\n",
           offsetof(sensor_record_t, sensor_id));

    printf("temperature offset: %zu\n",
           offsetof(sensor_record_t, temperature_centi_c));

    printf("timestamp offset: %zu\n",
           offsetof(sensor_record_t, timestamp_ms));

    printf("event_payload_t size: %zu bytes\n",
           sizeof(event_payload_t));

    printf("event_t size: %zu bytes\n",
           sizeof(event_t));
}

static int test_sensor_serialization(void)
{
    sensor_record_t sensor =
    {
        .sensor_id = 0x1234U,
        .temperature_centi_c = -550,
        .timestamp_ms = 0x12345678U
    };

    uint8_t output[SENSOR_RECORD_WIRE_SIZE] = {0U};

    event_model_status_t status =
        sensor_record_serialize_le(
            &sensor,
            output,
            sizeof(output));

    const uint8_t expected[SENSOR_RECORD_WIRE_SIZE] =
    {
        0x34U, 0x12U,
        0xDAU, 0xFDU,
        0x78U, 0x56U, 0x34U, 0x12U
    };

    if (status != EVENT_MODEL_OK)
    {
        printf("FAIL: serialization returned error\n");
        return 1;
    }

    for (size_t i = 0U; i < SENSOR_RECORD_WIRE_SIZE; i++)
    {
        if (output[i] != expected[i])
        {
            printf("FAIL: serialized byte %zu incorrect\n", i);
            return 1;
        }
    }

    printf("PASS: sensor serialization\n");
    return 0;
}

int main(void)
{
    int failures = 0;

    failures += test_sensor_serialization();
    failures += test_sensor_event();
    failures += test_button_event();
    failures += test_error_event();

    print_layout();

    if (failures == 0)
    {
        printf("All event model tests passed\n");
        return 0;
    }

    printf("%d event model test(s) failed\n", failures);
    return 1;
}