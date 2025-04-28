#ifndef __HCSR_H__
#define __HCSR_H__

#include "stm32f4xx_hal.h"

// Inisialisasi sensor HCSR04
void HCSR04_Init(void);

// Fungsi untuk memberi trigger ke sensor ultrasonik
void HCSR04_Trigger(void);

// Fungsi untuk membaca jarak hasil pengukuran
float HCSR04_ReadDistance(void);

// Fungsi untuk memeriksa dan merespons berdasarkan jarak dan kecepatan
void HCSR04_CheckAndReact(float speed_kmph);

#endif // __HCSR_H__
