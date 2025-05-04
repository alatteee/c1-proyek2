/* ----------------------------------------------------------------------------- */
/* File        : mobil.h                                                         */
/* Deskripsi   : Header untuk mengelola mobil dalam game dengan gambar (texture). */
/* ----------------------------------------------------------------------------- */

#ifndef MOBIL_H
#define MOBIL_H

#include <raylib.h>  // Library Raylib untuk grafik dan utilitas
#include "config.h"  // File konfigurasi game (ukuran layar, konstanta, dll.)

// Struktur untuk merepresentasikan mobil
typedef struct {
    float x;
    float y;
    float width;
    float height;
    Rectangle rect;
    int speed;
    bool isInvulnerable;
    float invulnerabilityTimer;
    Texture2D texture;  // Texture gambar mobil
} Car;

#define INVULNERABILITY_DURATION 2.0f  // Durasi invulnerability dalam detik

// Fungsi untuk menginisialisasi mobil dengan texture
void initCar(Car *car, float x, float y, float w, float h, int speed, const char *texturePath);

// Fungsi untuk merender mobil di layar
void renderCar(Car *car);

// Fungsi untuk menangani input gerakan mobil
void handleCarInput(Car *car);

// Fungsi untuk mereset posisi mobil ke posisi awal
void resetCarPosition(Car *car);

// Fungsi untuk memperbarui status invulnerability mobil
void updateCarInvulnerability(Car *car, float deltaTime);

// Fungsi untuk memeriksa tabrakan antara mobil dan rintangan
bool checkCarCollision(Car *car, Rectangle obstacle);

// Fungsi untuk unload texture mobil
void unloadCarTexture(Car *car);

#endif // MOBIL_H
