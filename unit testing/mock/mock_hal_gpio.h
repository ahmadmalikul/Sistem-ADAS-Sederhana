#ifndef MOCK_HAL_GPIO_H
#define MOCK_HAL_GPIO_H

#include <stdint.h>

typedef struct {
    int dummy;
} GPIO_TypeDef;

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0

void HAL_GPIO_WritePin(GPIO_TypeDef* port, uint16_t pin, uint8_t state);


#endif // MOCK_HAL_GPIO_H