/* ----------------------------------------------------------------------------- */
/* File        : mobil.c                                                         */
/* Deskripsi   : Implementasi untuk mengelola mobil dengan gambar (texture).     */
/* ----------------------------------------------------------------------------- */

#include "../include/mobil.h"
#include "../include/config.h"
#include "../include/lives.h"
#include <raylib.h>
#include <stdio.h>

// Fungsi untuk menginisialisasi mobil dengan texture
void initCar(Car *car, float x, float y, float width, float height, int speed, const char *texturePath) {
    car->x = x;
    car->y = y;
    car->width = width;
    car->height = height;
    car->speed = speed;
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
    car->isInvulnerable = false;
    car->invulnerabilityTimer = 0.0f;
    car->texture = LoadTexture(texturePath);  // Load gambar mobil
}

// Fungsi untuk merender mobil di layar
void renderCar(Car *car) {
  Vector2 position = { car->x, car->y };
  float scaleX = car->width / (float)car->texture.width;
  DrawTextureEx(car->texture, position, 0.0f, scaleX * 1.5f, WHITE);
}

// Fungsi untuk menangani input gerakan mobil
void handleCarInput(Car *car) {
    if (IsKeyDown(KEY_LEFT))
        car->x -= car->speed;
    if (IsKeyDown(KEY_RIGHT))
        car->x += car->speed;
    if (IsKeyDown(KEY_UP))
        car->y -= car->speed;
    if (IsKeyDown(KEY_DOWN))
        car->y += car->speed;

    // Batasi mobil agar tidak keluar dari layar
    if (car->x < 0) car->x = 0;
    if (car->x + car->width > SCREEN_WIDTH) car->x = SCREEN_WIDTH - car->width;
    if (car->y < 0) car->y = 0;
    if (car->y + car->height > SCREEN_HEIGHT) car->y = SCREEN_HEIGHT - car->height;

    // Update rectangle mobil
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Fungsi untuk mereset posisi mobil ke posisi awal
void resetCarPosition(Car *car) {
    car->x = MIDDLE_LANE_X;
    car->y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f;
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Fungsi untuk memperbarui status invulnerability mobil
void updateCarInvulnerability(Car *car, float deltaTime) {
    if (car->isInvulnerable) {
        car->invulnerabilityTimer += deltaTime;
        if (car->invulnerabilityTimer >= INVULNERABILITY_DURATION) {
            car->isInvulnerable = false;
            car->invulnerabilityTimer = 0.0f;
        }
    }
}

// Fungsi untuk memeriksa tabrakan antara mobil dan rintangan
bool checkCarCollision(Car *car, Rectangle obstacle) {
    if (!car->isInvulnerable && CheckCollisionRecs(car->rect, obstacle)) {
        TraceLog(LOG_INFO, "Tabrakan terdeteksi!");
        car->isInvulnerable = true;
        car->invulnerabilityTimer = 0.0f;
        return true;
    }
    return false;
}

// Fungsi untuk unload texture mobil
void unloadCarTexture(Car *car) {
    UnloadTexture(car->texture);
}
