#include "HCSR.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "mock_hal_gpio.h"
#include "mock_hal_uart.h"
#include "mock_hal_delay.h"

float distance = 0;
uint8_t rem_aktif = 0;

#define REM_PIN 5
#define BUZZER_PIN 6
#define SOLENOID_PIN 7

float HCSR04_ReadDistance(void) {
    return distance;
}

void HCSR04_SafetyCheckAndControl(float speed_kmph) {
    char msg[64];

    // Validasi jarak sensor
    if (distance <= 0.0f || distance > 400.0f) {
        char invalid[] = "Jarak tidak valid.\r\n";
        HAL_UART_Transmit(NULL, (uint8_t*)invalid, strlen(invalid), 1000);
        return;
    }

    sprintf(msg, "Jarak: %.2f cm | Kecepatan: %.2f km/jam\r\n", distance, speed_kmph);
    HAL_UART_Transmit(NULL, (uint8_t*)msg, strlen(msg), 1000);

    // Cek jika jarak <= 150 cm
    if (distance <= 150.0f) {
        if (speed_kmph < 40.0f) {
            // Kecepatan kurang dari 40 km/jam, nyalakan buzzer
            char warning[] = "Peringatan: Jarak dekat! Kecepatan terlalu rendah, aktifkan buzzer.\r\n";
            HAL_UART_Transmit(NULL, (uint8_t*)warning, strlen(warning), 1000);

            // Aktifkan buzzer
            HAL_GPIO_WritePin(NULL, BUZZER_PIN, GPIO_PIN_SET);
            HAL_Delay(100);
            HAL_GPIO_WritePin(NULL, BUZZER_PIN, GPIO_PIN_RESET);
        } else if (speed_kmph >= 40.0f) {
            // Kecepatan lebih dari 40 km/jam, nyalakan motor solenoid dan tarik tuas rem
            char action[] = "Kecepatan tinggi! Mengaktifkan rem.\r\n";
            HAL_UART_Transmit(NULL, (uint8_t*)action, strlen(action), 1000);

            // Nyalakan motor solenoid untuk menarik rem
            HAL_GPIO_WritePin(NULL, SOLENOID_PIN, GPIO_PIN_SET);
            HAL_Delay(500);  // Sesuaikan dengan durasi yang diinginkan untuk penarikan rem

            // Matikan motor solenoid setelah menarik rem
            HAL_GPIO_WritePin(NULL, SOLENOID_PIN, GPIO_PIN_RESET);

            // Menarik rem perlahan
            HAL_GPIO_WritePin(NULL, REM_PIN, GPIO_PIN_SET);  // Mulai tarik rem
            HAL_Delay(200);  // Sesuaikan durasi penarikan rem perlahan
            HAL_GPIO_WritePin(NULL, REM_PIN, GPIO_PIN_RESET);  // Rem dilepaskan
        }
    } else {
        // Jika jarak lebih dari 150 cm, pastikan rem dalam posisi tidak aktif
        HAL_GPIO_WritePin(NULL, REM_PIN, GPIO_PIN_RESET);
        rem_aktif = 0;
    }
}
