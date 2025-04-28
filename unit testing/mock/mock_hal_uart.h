#ifndef MOCK_HAL_UART_H
#define MOCK_HAL_UART_H

#include <stdint.h>
#include <string.h>

void HAL_UART_Transmit(void* huart, uint8_t* data, uint16_t size, uint32_t timeout);

#endif  // MOCK_HAL_UART_H
