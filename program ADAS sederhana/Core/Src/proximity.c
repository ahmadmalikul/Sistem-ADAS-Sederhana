#include "Proximity.h"
#include "HCSR.h"  // Mengakses nilai jarak dari sensor HCSR04

#define BUZZER_PORT GPIOB
#define BUZZER_PIN  GPIO_PIN_10  // Ganti sesuai dengan pin buzzer kamu
#define DISTANCE_THRESHOLD 10.0f  // Ambang batas jarak untuk mengaktifkan buzzer (dalam cm)

extern float distance;  // Ambil nilai jarak dari modul HCSR04

// Fungsi untuk menginisialisasi pin GPIO untuk buzzer
void Proximity_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Aktifkan clock port buzzer (contoh: GPIOB)
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Konfigurasi pin buzzer sebagai output push-pull
    GPIO_InitStruct.Pin = BUZZER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

    // Matikan buzzer di awal
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

// Fungsi untuk memeriksa jarak dan mengaktifkan buzzer
void Proximity_CheckAndActivate(void)
{
    // Periksa apakah jarak kurang dari ambang batas
    if (distance < DISTANCE_THRESHOLD) {
        // Aktifkan buzzer jika jarak terlalu dekat
        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);  // Buzzer ON
    } else {
        // Matikan buzzer jika jarak aman
        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);  // Buzzer OFF
    }
}
