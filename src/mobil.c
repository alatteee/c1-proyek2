/* ----------------------------------------------------------------------------- */
/* File        : mobil.c                                                         */
/* Deskripsi   : Implementasi untuk mengelola mobil dengan gambar (texture).     */
/* ----------------------------------------------------------------------------- */

#include "../include/mobil.h"
#include "../include/config.h"
#include "../include/lives.h"
#include "../include/rintangan.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// Helper function untuk mendapatkan posisi X dari lane
float getLaneXPosition(LanePosition lane) {
    switch (lane) {
        case LANE_LEFT:
            return LEFT_LANE_X;
        case LANE_MIDDLE:
            return MIDDLE_LANE_X;
        case LANE_RIGHT:
            return RIGHT_LANE_X;
        default:
            return MIDDLE_LANE_X;
    }
}

// Menginisialisasi mobil dengan posisi dan ukuran tertentu
void initCar(Car *car, float x, float y, float width, float height, float speed, const char *texturePath) {
    car->x = x;
    car->y = y;
    car->width = width;
    car->height = height;
    car->speed = speed;
    car->rect = (Rectangle){x, y, width, height};
    car->isInvulnerable = false;
    car->invulnerabilityTime = 0.0f;
    strcpy(car->texturePath, texturePath);
    car->texture = LoadTexture(texturePath);
    
    // Initialize lane-based movement (teleport system only)
    car->currentLane = LANE_MIDDLE;
    
    // Log jika texture berhasil dimuat
    if (car->texture.id > 0) {
        printf("Car texture loaded successfully: %s (%dx%d)\n", 
               texturePath, car->texture.width, car->texture.height);
    } else {
        printf("Failed to load car texture: %s\n", texturePath);
    }
}

// Menggambar mobil dengan texture (dengan efek invulnerable) - ukuran naik 15%
void renderCar(Car *car) {
    // Tentukan warna berdasarkan status invulnerable (kedip-kedip saat invulnerable)
    Color tint = WHITE;
    if (car->isInvulnerable) {
        // Efek kedip-kedip dengan menggunakan sin untuk transparansi
        float alpha = (sin(car->invulnerabilityTime * 10.0f) + 1.0f) / 2.0f;
        tint = (Color){255, 255, 255, (unsigned char)(alpha * 255)};
    }
    
    // Hitung rasio aspek asli dari texture
    float originalAspectRatio = (float)car->texture.width / (float)car->texture.height;
    
    // Mulai dengan ukuran berdasarkan lebar yang dialokasikan (naik 15%)
    float renderWidth = car->width * 1.15f;
    float renderHeight = renderWidth / originalAspectRatio;
    
    // Faktor skala untuk menjaga proporsionalitas dalam area yang dialokasikan
    float scaleFactor = 1.0f; // 100% dari area yang dialokasikan
    
    // Jika tinggi hasil lebih besar dari tinggi yang tersedia, sesuaikan ulang
    if (renderHeight > car->height * scaleFactor * 1.15f) {
        renderHeight = car->height * scaleFactor * 1.15f;
        renderWidth = renderHeight * originalAspectRatio;
    }
    
    // Hitung offset untuk memusatkan mobil pada area yang dialokasikan
    float offsetX = (car->width - renderWidth) / 2;
    float offsetY = (car->height - renderHeight) / 2;
    
    DrawTexturePro(
        car->texture,
        (Rectangle){0, 0, car->texture.width, car->texture.height},
        (Rectangle){car->x + offsetX, car->y + offsetY, renderWidth, renderHeight},
        (Vector2){0, 0},
        0.0f,
        tint);
        
    // Rectangle untuk collision detection menggunakan ukuran yang diperbesar
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Function untuk teleport mobil ke lane tertentu
void teleportToLane(Car *car, LanePosition targetLane) {
    if (car->currentLane == targetLane) {
        return; // Sudah di lane target
    }
    
    car->currentLane = targetLane;
    car->x = getLaneXPosition(targetLane);
    
    // Perbarui rectangle untuk collision detection
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
    
    printf("Teleported to lane %d at position X: %.2f\n", car->currentLane, car->x);
}

// Memindahkan mobil berdasarkan input pemain (teleport antar lane)
void handleCarInput(Car *car) {
    // Input untuk pindah lane (teleport) - ALWAYS WORKS, no blocking conditions
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (car->currentLane > LANE_LEFT) {
            teleportToLane(car, car->currentLane - 1);
        }
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (car->currentLane < LANE_RIGHT) {
            teleportToLane(car, car->currentLane + 1);
        }
    }
    
    // Kontrol vertikal tetap bisa digunakan
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        car->y -= car->speed;
        if (car->y < 0) car->y = 0;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        car->y += car->speed;
        if (car->y > SCREEN_HEIGHT - car->height) car->y = SCREEN_HEIGHT - car->height;
    }
    
    // Perbarui rectangle untuk collision detection
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Fungsi lama: Memeriksa tabrakan antara mobil dan rintangan
bool checkCarCollision(Car *car, Rectangle obstacle) {
    if (!car->isInvulnerable && CheckCollisionRecs(car->rect, obstacle)) {
        TraceLog(LOG_INFO, "Tabrakan terdeteksi!");
        car->isInvulnerable = true;
        car->invulnerabilityTime = INVULNERABILITY_DURATION;
        return true;
    }
    return false;
}

// Fungsi baru: Memeriksa tabrakan dengan sistem obstacle linked list
bool checkCarObstacleCollision(Car *car) {
    if (car->isInvulnerable) return false;
    
    int collisions = checkCollision(car->x, car->y, car->width, car->height);
    if (collisions > 0) {
        TraceLog(LOG_INFO, "Tabrakan terdeteksi dengan DLL rintangan!");
        car->isInvulnerable = true;
        car->invulnerabilityTime = INVULNERABILITY_DURATION;
        return true;
    }
    return false;
}

// Memperbarui status invulnerability mobil
void updateCarInvulnerability(Car *car, float deltaTime) {
    if (car->isInvulnerable) {
        car->invulnerabilityTime -= deltaTime;
        if (car->invulnerabilityTime <= 0) {
            car->isInvulnerable = false;
        }
    }
}

// Membebaskan resource mobil
void unloadCar(Car *car) {
    UnloadTexture(car->texture);
}

// Alias untuk unloadCar (untuk kompatibilitas dengan mobil_selection.c)
void unloadCarTexture(Car *car) {
    UnloadTexture(car->texture);
}