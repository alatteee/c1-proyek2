#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <stdbool.h>
#include <raylib.h>
#include "config.h"  // Make sure this contains definitions for SCREEN_WIDTH, SCREEN_HEIGHT, etc.

// Mendeklarasikan struktur Rintangan yang berisi data tentang rintangan dalam permainan
typedef struct Rintangan {
    float x, y;          // Posisi X dan Y rintangan
    float width, height; // Ukuran (lebar dan tinggi) rintangan
    int type;            // Jenis rintangan (misalnya, jenis objek yang digunakan untuk membedakan tipe rintangan)
    bool hasPassed;      // Status apakah rintangan sudah dilewati oleh pemain
    bool hasCollided;    // Flag untuk menandai apakah rintangan sudah bertabrakan dengan mobil
} Rintangan;

// Mendeklarasikan array rintangan yang menyimpan data rintangan untuk setiap jalur (MAX_LANES) dan untuk setiap posisi rintangan (MAX_OBSTACLES)
extern Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

// Fungsi untuk menginisialisasi rintangan di layar
void initRintangan();
// Fungsi untuk memperbarui posisi dan status rintangan
void updateRintangan();
// Fungsi untuk memeriksa apakah terjadi tabrakan antara objek tertentu dan rintangan
int checkCollision(float x, float y, float width, float height);

// Mendeklarasikan fungsi untuk menggambar rintangan di layar
void drawRintangan();

#endif // RINTANGAN_H