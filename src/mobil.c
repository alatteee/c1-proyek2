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

// Fungsi untuk menggambar mobil dengan kotak-kotak
void renderCar(SDL_Renderer* renderer, Car* car) {
    // Warna untuk tubuh mobil
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);  // Warna biru untuk tubuh mobil

    // Gambar bagian tubuh mobil (kotak besar)
    SDL_FRect mainBody = { car->rect.x + 10.0f, car->rect.y + 20.0f, car->rect.w - 20.0f, car->rect.h - 40.0f };
    SDL_RenderFillRect(renderer, &mainBody); // Bagian tubuh mobil

    // Gambar kotak-kotak kecil di dalam tubuh mobil (seperti pola di gambar)
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);  // Warna oranye untuk kotak kecil
    float boxWidth = car->rect.w / 3;  // Lebar kotak kecil
    float boxHeight = car->rect.h / 5;  // Tinggi kotak kecil

    float i, j;
    // Susun kotak kecil di dalam tubuh mobil (pola kotak teratur)
    for (i = 0; i < 3; i++) {  // Tiga kolom
        for (j = 0; j < 3; j++) {  // Tiga baris
            SDL_FRect smallBox = {
                car->rect.x + 10.0f + i * boxWidth, 
                car->rect.y + 20.0f + j * boxHeight, 
                boxWidth, 
                boxHeight
            };
            SDL_RenderFillRect(renderer, &smallBox);  // Gambar kotak kecil
        }
    }

    // Gambar bagian bawah mobil (basis mobil)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Merah untuk bagian bawah
    SDL_FRect bottom = { car->rect.x, car->rect.y + car->rect.h - 20.0f, car->rect.w, 20.0f };
    SDL_RenderFillRect(renderer, &bottom); // Bagian bawah mobil
}