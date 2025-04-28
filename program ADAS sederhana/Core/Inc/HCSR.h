#ifndef __HCSR04_H
#define __HCSR04_H

#include "stm32f4xx_hal.h"

// Inisialisasi sensor HC-SR04
void HCSR04_Init(void);

// Fungsi untuk membaca jarak
float HCSR04_ReadDistance(void);

// Fungsi untuk mengecek jarak dan mengendalikan rem berdasarkan kecepatan
void HCSR04_SafetyCheckAndControl(float speed_kmph);

// Fungsi untuk mengirimkan pulsa trigger
void HCSR04_Trigger(void);

// Fungsi untuk delay mikrodetik
void delay_us(uint16_t us);

#endif
