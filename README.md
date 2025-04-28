#Pemrograman Kontroller
# Sistem ADAS Sederhana dengan STM32

Proyek ini merupakan implementasi sistem *Advanced Driver Assistance System (ADAS)* sederhana menggunakan *STM32*. Sistem ini menggunakan sensor jarak (seperti ultrasonic) dan sensor (infrared) untuk mengontrol motor solenoid dan buzzer, dengan tujuan meningkatkan keselamatan kendaraan.

## Kerja Sistem
1. *Jika jarak kurang dari 1,5 meter dan kecepatan lebih dari 40 km/jam*: 
   - Motor solenoid akan mengaktifkan dan menarik tuas rem secara perlahan.
   
2. *Jika jarak kurang dari 1,5 meter dan kecepatan kurang dari 40 km/jam*: 
   - Buzzer akan menyala sebagai peringatan.

## Fitur
- Mengukur jarak menggunakan sensor ultrasonic ( HC-SR04) dan Sensor (proximity).
- Mengaktifkan motor solenoid untuk menarik tuas rem secara perlahan.
- Menyalakan buzzer sebagai peringatan.

## Instalasi

Untuk menjalankan proyek ini, ikuti langkah-langkah berikut:

1. *Clone Repository:*
   Clone repositori ini ke komputer lokal Anda:
   ```bash
   git clone https://github.com/username/my-project.git
