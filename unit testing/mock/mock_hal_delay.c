#include "mock_hal_delay.h"
#include <stdio.h>

void HAL_Delay(uint32_t ms) {
    printf("Delay %u ms\n", ms);
}