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

// Fungsi untuk menggambar mobil dengan kotak kecil yang disusun
void renderCar(SDL_Renderer* renderer, Car* car) {
    // Warna untuk tubuh mobil
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Merah untuk tubuh mobil

    // Gambar bagian tubuh mobil (kotak besar)
    SDL_FRect mainBody = { car->rect.x + 10.0f, car->rect.y + 20.0f, car->rect.w - 20.0f, car->rect.h - 40.0f };
    SDL_RenderFillRect(renderer, &mainBody); // Bagian tubuh mobil

    // Gambar kotak kecil di dalam tubuh mobil (seperti pola di gambar)
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);  // Warna biru untuk kotak kecil
    float boxWidth = car->rect.w / 2;  // Lebar kotak kecil
    float boxHeight = car->rect.h / 4;  // Tinggi kotak kecil

    // Susun kotak kecil di tengah tubuh mobil
    float i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
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

    // Ganti warna roda menjadi hitam
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Hitam untuk roda

    // Gambar roda mobil
    SDL_FRect wheel1 = { car->rect.x + 10.0f, car->rect.y + car->rect.h - 15.0f, 25.0f, 15.0f };
    SDL_FRect wheel2 = { car->rect.x + car->rect.w - 35.0f, car->rect.y + car->rect.h - 15.0f, 25.0f, 15.0f };
    SDL_RenderFillRect(renderer, &wheel1); // Roda kiri
    SDL_RenderFillRect(renderer, &wheel2); // Roda kanan
}