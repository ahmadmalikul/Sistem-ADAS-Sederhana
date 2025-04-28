#include "HCSR.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;

uint32_t ic_val1 = 0;
uint32_t ic_val2 = 0;
uint8_t is_first_captured = 0;
uint32_t difference = 0;
float distance = 0;
uint8_t rem_aktif = 0;

// Fungsi delay mikrodetik
void delay_us(uint16_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000);
    while ((DWT->CYCCNT - start) < ticks);
}

// Inisialisasi sensor HC-SR04
void HCSR04_Init(void) {
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);

    // Aktifkan DWT counter untuk delay mikrodetik (jika belum aktif)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

// Kirim pulsa trigger ke sensor HC-SR04
void HCSR04_Trigger(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);  // Matikan Trigger
    delay_us(2);  // Tunggu 2 us
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);    // Nyalakan Trigger
    delay_us(10); // Tunggu 10 us
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);  // Matikan Trigger
}

// Baca jarak dari sensor
float HCSR04_ReadDistance(void) {
    HCSR04_Trigger();     // Kirim pulsa trigger
    HAL_Delay(60);        // Tunggu sensor memproses data
    return distance;      // Kembalikan nilai jarak
}

// Callback untuk menangkap sinyal Echo
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        if (is_first_captured == 0) {
            ic_val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Tangkap waktu pertama
            is_first_captured = 1;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING); // Set polaritas falling edge
        } else {
            ic_val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Tangkap waktu kedua
            if (ic_val2 > ic_val1) {
                difference = ic_val2 - ic_val1;  // Hitung selisih waktu
            } else {
                difference = (0xFFFF - ic_val1 + ic_val2);  // Hitung selisih jika terjadi overflow
            }
            distance = (difference * 0.034f) / 2.0f;  // Hitung jarak (cm)
            is_first_captured = 0;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); // Set polaritas rising edge
        }
    }
}

// Fungsi utama pengendali safety berdasarkan jarak dan kecepatan
void HCSR04_SafetyCheckAndControl(float speed_kmph) {
    char msg[64];
    float jarak = HCSR04_ReadDistance();  // Baca jarak

    // Validasi jarak
    if (jarak <= 0.0f || jarak > 400.0f) {
        char invalid[] = "Jarak tidak valid.\r\n";
        HAL_UART_Transmit(&huart2, (uint8_t*)invalid, strlen(invalid), HAL_MAX_DELAY);
        return;
    }

    // Kirim informasi jarak dan kecepatan via UART
    sprintf(msg, "Jarak: %.2f cm | Kecepatan: %.2f km/jam\r\n", jarak, speed_kmph);
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    // Pengendalian rem (solenoid) berdasarkan jarak dan kecepatan
    if (jarak <= 150.0f) {
        if (speed_kmph > 40.0f) {
            if (!rem_aktif) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);  // Aktifkan solenoid (rem)
                HAL_Delay(100);  // Rem aktif sejenak
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // Matikan solenoid
                rem_aktif = 1;  // Set flag rem aktif
            }
        } else {
            char warning[] = "Peringatan: Jarak dekat! Kurangi kecepatan.\r\n";
            HAL_UART_Transmit(&huart2, (uint8_t*)warning, strlen(warning), HAL_MAX_DELAY);
        }
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // Lepaskan rem jika tidak ada ancaman
        rem_aktif = 0;  // Reset flag rem aktif
    }
}
