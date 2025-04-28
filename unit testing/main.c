#include "hcsr/HCSR.h"
#include "proximity/proximity.h"
#include <stdio.h>

extern float distance;
void main() {
    float speed_kmph = 30.0f;  // Contoh kecepatan
    distance = 150.0f;  // Set jarak (misalnya 80 cm)

    // Memanggil fungsi untuk memeriksa jarak dan kecepatan
    HCSR04_SafetyCheckAndControl(speed_kmph);

    // Memanggil fungsi proximity untuk cek jarak
    Proximity_CheckAndActivate();
}