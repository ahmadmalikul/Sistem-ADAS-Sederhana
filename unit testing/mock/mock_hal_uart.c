#include <stdint.h>
#include <stddef.h>

// Dummy implementation
void HAL_UART_Transmit(void *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
    // You can optionally print or log something here
}
// This is a mock function for unit testing purposes
// It simulates the behavior of the HAL_UART_Transmit function from STM32 HAL library