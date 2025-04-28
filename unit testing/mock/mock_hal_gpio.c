#include "mock_hal_gpio.h"
#include <stdio.h>

void HAL_GPIO_WritePin(GPIO_TypeDef* port, uint16_t pin, uint8_t state) 

    {
    printf("Mock GPIO Write: port=%d, pin=%d, state=%d\n", port, pin, state);
}

void HAL_UART_Transmit(void *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
    printf("Mock UART Transmit: %s\n", (char*)pData);
}

void HAL_Delay(uint32_t Delay) {
    printf("Mock Delay: %lu ms\n", Delay);
}
