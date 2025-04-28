#ifndef __PROXIMITY_H
#define __PROXIMITY_H

#include "stm32f4xx_hal.h"

void Proximity_Init(void);

// Fungsi untuk memeriksa apakah objek berada dalam jarak < 1.5 meter
uint8_t Proximity_IsInRange(void);

#endif
