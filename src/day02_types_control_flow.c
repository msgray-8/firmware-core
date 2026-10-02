#include <stdint.h>
#include <stdio.h>

#define ADC_MAX_VALUE 4095U
#define ADC_REFERENCE_MV 3300U

uint32_t sample_to_millivolts(uint16_t sample)
{
    if (sample > ADC_MAX_VALUE)
    {
        return UINT32_MAX;
    }

    uint32_t mv =
        (uint32_t)sample * ADC_REFERENCE_MV / ADC_MAX_VALUE;

    return mv;
}

int main(void)
{
    uint16_t samples[] = {0U, 2048U, 4095U, 4096U};

    for (uint32_t i = 0U; i < 4U; i++)
    {
        uint32_t mv = sample_to_millivolts(samples[i]);

        if (mv == UINT32_MAX)
        {
            printf("Sample %u: Invalid sample\n",
                   (unsigned int)samples[i]);
        }
        else
        {
            printf("Sample %u: %u mV\n",
                   (unsigned int)samples[i],
                   (unsigned int)mv);
        }
    }

    return 0;
}