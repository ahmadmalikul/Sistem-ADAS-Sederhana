#ifndef PROXIMITY_H
#define PROXIMITY_H

#include "stm32f4xx_hal.h"  // Pastikan untuk menyertakan header yang sesuai dengan perangkat STM32

// Deklarasi fungsi untuk menginisialisasi buzzer
void Proximity_Init(void);

// Deklarasi fungsi untuk memeriksa jarak dan mengendalikan buzzer
void Proximity_CheckAndActivate(void);
uint8_t Proximity_IsInRange(void);
#endif /* PROXIMITY_H */
