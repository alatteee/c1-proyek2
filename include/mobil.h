/* ----------------------------------------------------------------------------- */
/* File        : mobil.h                                                         */
/* Deskripsi   : File header untuk mengelola mobil dalam game. Berisi definisi   */
/*              struktur Car dan fungsi-fungsi untuk menginisialisasi, menggerak-*/
/*              kan, merender, dan menangani logika mobil, termasuk invulnerabi- */
/*              lity dan deteksi tabrakan.                                      */
/* ----------------------------------------------------------------------------- */

#ifndef MOBIL_H
#define MOBIL_H

#include <raylib.h>  // Library Raylib untuk grafik dan utilitas
#include "config.h"  // File konfigurasi game (ukuran layar, konstanta, dll.)

// Struktur untuk merepresentasikan mobil
typedef struct {
    float x;                      // Posisi X mobil
    float y;                      // Posisi Y mobil
    float width;                  // Lebar mobil
    float height;                 // Tinggi mobil
    Rectangle rect;               // Bentuk persegi panjang mobil (untuk collision detection)
    int speed;                    // Kecepatan mobil
    bool isInvulnerable;          // Status apakah mobil sedang invulnerable (tidak bisa tertabrak)
    float invulnerabilityTimer;   // Timer untuk durasi invulnerability
} Car;

#define INVULNERABILITY_DURATION 2.0f  // Durasi invulnerability dalam detik

// Fungsi untuk menginisialisasi mobil
// Parameter:
// - car: Pointer ke objek Car yang akan diinisialisasi
// - x: Posisi X awal mobil
// - y: Posisi Y awal mobil
// - w: Lebar mobil
// - h: Tinggi mobil
// - speed: Kecepatan mobil
void initCar(Car *car, float x, float y, float w, float h, int speed);

// Fungsi untuk menggerakkan mobil ke kiri
// Parameter:
// - car: Pointer ke objek Car
void moveLeft(Car *car);

// Fungsi untuk menggerakkan mobil ke kanan
// Parameter:
// - car: Pointer ke objek Car
// - screenWidth: Lebar layar (untuk mencegah mobil keluar dari layar)
void moveRight(Car *car, int screenWidth);

// Fungsi untuk merender mobil di layar
// Parameter:
// - car: Pointer ke objek Car
void renderCar(Car *car);

// Fungsi untuk menangani input pengguna (gerakan mobil)
// Parameter:
// - cars: Array atau pointer ke objek Car
void handleCarInput(Car *cars);

// Fungsi untuk mereset posisi mobil ke posisi awal
// Parameter:
// - car: Pointer ke objek Car
void resetCarPosition(Car *car);

// Fungsi untuk memperbarui status invulnerability mobil
// Parameter:
// - car: Pointer ke objek Car
// - deltaTime: Waktu yang telah berlalu sejak frame terakhir (dalam detik)
void updateCarInvulnerability(Car *car, float deltaTime);

// Fungsi untuk memeriksa tabrakan antara mobil dan rintangan
// Parameter:
// - car: Pointer ke objek Car
// - obstacle: Rectangle yang merepresentasikan rintangan
// Return: true jika terjadi tabrakan, false jika tidak
bool checkCarCollision(Car *car, Rectangle obstacle);

#endif // MOBIL_H