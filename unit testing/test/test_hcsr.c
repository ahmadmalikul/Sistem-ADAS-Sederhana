#include "HCSR.h"
#include <stdio.h>

extern float distance;

int main() {
    printf("\n--- Test HCSR Safety Control ---\n");
    distance = 140.0f;
    HCSR04_SafetyCheckAndControl(45.0f);
    distance = 140.0f;
    HCSR04_SafetyCheckAndControl(35.0f);
    distance = 200.0f;
    HCSR04_SafetyCheckAndControl(30.0f);
    return 0;
}