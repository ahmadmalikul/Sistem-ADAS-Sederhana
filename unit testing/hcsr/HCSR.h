#ifndef HCSR_H
#define HCSR_H

float HCSR04_ReadDistance(void);
void HCSR04_SafetyCheckAndControl(float speed_kmph);

// Gunakan extern agar bisa diakses dari file lain
extern float distance;

#endif
// HCSR_H