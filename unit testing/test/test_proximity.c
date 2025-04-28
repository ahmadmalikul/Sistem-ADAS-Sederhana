#include <stdio.h>
#include "HCSR.h"
#include "Proximity.h"

// Gunakan extern untuk akses variabel dari HCSR.c
extern float distance;

int main() {
    printf("--- Test Proximity ---\n");

    // Simulasi 1: Jarak dekat, kecepatan tinggi → aktifkan rem
    distance = 100.0f;
    printf("Simulasi 1: Jarak = %.2f cm, Kecepatan = 60 km/jam\n", distance);
    HCSR04_SafetyCheckAndControl(60.0f);

    // Simulasi 2: Jarak dekat, kecepatan rendah → buzzer warning
    distance = 80.0f;
    printf("Simulasi 2: Jarak = %.2f cm, Kecepatan = 30 km/jam\n", distance);
    HCSR04_SafetyCheckAndControl(30.0f);

    // Simulasi 3: Jarak jauh → tidak ada aksi
    distance = 250.0f;
    printf("Simulasi 3: Jarak = %.2f cm, Kecepatan = 70 km/jam\n", distance);
    HCSR04_SafetyCheckAndControl(70.0f);

    // Simulasi 4: Proximity logic → aktifkan buzzer jika jarak < 100
    distance = 90.0f;
    printf("Simulasi 4: Proximity Check (buzzer jika < 100)\n");
    Proximity_CheckAndActivate();

    return 0;
}
