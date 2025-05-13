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
    
    // Log jika texture berhasil dimuat
    if (car->texture.id > 0) {
        TraceLog(LOG_INFO, "Car texture loaded successfully: %s", texturePath);
    } else {
        TraceLog(LOG_ERROR, "Failed to load car texture: %s", texturePath);
    }
}

// Menggambar mobil dengan texture
void renderCar(Car *car) {
    // Gunakan alpha untuk efek invulnerable
    Color tint = car->isInvulnerable ? 
                (((int)(car->invulnerabilityTime * 10) % 2 == 0) ? 
                 GRAY : WHITE) : WHITE;
    
    // Hitung rasio aspek asli dari texture
    float originalAspectRatio = (float)car->texture.width / (float)car->texture.height;
    
    // Faktor skala untuk ukuran mobil (25% lebih besar)
    float scaleFactor = 1.25f;
    
    // Hitung ukuran render yang mempertahankan rasio aspek dengan faktor skala baru
    float renderWidth = car->width * scaleFactor;
    float renderHeight = renderWidth / originalAspectRatio;
    
    // Jika tinggi hasil lebih besar dari tinggi yang tersedia, sesuaikan ulang
    if (renderHeight > car->height * scaleFactor) {
        renderHeight = car->height * scaleFactor;
        renderWidth = renderHeight * originalAspectRatio;
    }
    
    // Hitung offset untuk memusatkan mobil pada area yang dialokasikan
    // (offset negatif untuk mobil yang lebih besar agar tetap di tengah)
    float offsetX = (car->width - renderWidth) / 2;
    float offsetY = (car->height - renderHeight) / 2;
    
    DrawTexturePro(
        car->texture,
        (Rectangle){0, 0, car->texture.width, car->texture.height},
        (Rectangle){car->x + offsetX, car->y + offsetY, renderWidth, renderHeight},
        (Vector2){0, 0},
        0.0f,
        tint);
        
    // Rectangle untuk collision detection tetap menggunakan ukuran asli
    // untuk menjaga gameplay balance
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Memindahkan mobil berdasarkan input pemain
void handleCarInput(Car *car) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        car->x -= car->speed;
        if (car->x < 0) car->x = 0;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        car->x += car->speed;
        if (car->x > SCREEN_WIDTH - car->width) car->x = SCREEN_WIDTH - car->width;
    }
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