/* ----------------------------------------------------------------------------- */
/* File        : mobil.h                                                         */
/* Deskripsi   : Header untuk mengelola mobil dalam game dengan gambar (texture). */
/* ----------------------------------------------------------------------------- */

#ifndef MOBIL_H
#define MOBIL_H

#include <raylib.h>  // Library Raylib untuk grafik dan utilitas
#include "config.h"  // Include config untuk LanePosition

// Konstanta untuk invulnerability setelah tabrakan
#define INVULNERABILITY_DURATION 2.0f  // Durasi dalam detik

// Struktur mobil yang menyimpan informasi posisi, ukuran, dan tekstur
typedef struct {
    float x;              // Posisi x mobil
    float y;              // Posisi y mobil
    float width;          // Lebar mobil
    float height;         // Tinggi mobil
    float speed;          // Kecepatan mobil
    Rectangle rect;       // Rectangle untuk collision detection
    Texture2D texture;    // Texture mobil
    bool isInvulnerable;  // Status invulnerable
    float invulnerabilityTime;  // Timer invulnerable (dalam detik)
    char texturePath[100]; // Path ke file texture
    
    // Lane-based movement variables (teleport system only)
    LanePosition currentLane;    // Lane saat ini
} Car;

// Menginisialisasi mobil dengan posisi dan ukuran tertentu
void initCar(Car *car, float x, float y, float width, float height, float speed, const char *texturePath);

// Menggambar mobil dengan texture
void renderCar(Car *car);

// Memindahkan mobil berdasarkan input pemain (teleport antar lane)
void handleCarInput(Car *car);

// Memeriksa tabrakan antara mobil dan rintangan (untuk kompatibilitas dengan kode lama)
bool checkCarCollision(Car *car, Rectangle obstacle);

// Memperbarui status invulnerability mobil
void updateCarInvulnerability(Car *car, float deltaTime);

// Membebaskan resource mobil
void unloadCar(Car *car);

// Alias untuk kompatibilitas dengan mobil_selection.c
void unloadCarTexture(Car *car);

// Fungsi untuk memeriksa tabrakan dengan sistem double linked list obstacle
bool checkCarObstacleCollision(Car *car);

// Fungsi helper untuk lane management
float getLaneXPosition(LanePosition lane);
void teleportToLane(Car *car, LanePosition targetLane);

#endif // MOBIL_H