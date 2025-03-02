#include "../include/mobil.h"

// Fungsi untuk inisialisasi mobil
void initCar(Car* car, float x, float y, float width, float height, int speed) {
    car->x = x;
    car->y = y;
    car->width = width;
    car->height = height;
    car->speed = speed;
    car->rect.x = x;
    car->rect.y = y;
    car->rect.w = width;
    car->rect.h = height;
}

// Fungsi untuk menggerakkan mobil ke kiri
void moveLeft(Car* car) {
    if (car->x > 0) {
        car->x -= car->speed;
        car->rect.x = car->x;
    }
}

// Fungsi untuk menggerakkan mobil ke kanan
void moveRight(Car* car, int screenWidth) {
    if (car->x + car->width < screenWidth) {
        car->x += car->speed;  // Menggunakan kecepatan yang benar
        car->rect.x = car->x;
    }
}

// Fungsi untuk menggambar mobil
void renderCar(SDL_Renderer* renderer, Car* car) {
    SDL_RenderFillRect(renderer, &car->rect);  // Menggunakan SDL_FRect di SDL3
}
