#ifndef MOBIL_H
#define MOBIL_H

#include <SDL3/SDL.h>

// Struktur untuk mobil
typedef struct {
    float x;               // Posisi X mobil
    float y;               // Posisi Y mobil
    float width;           // Lebar mobil
    float height;          // Tinggi mobil
    SDL_FRect rect;        // SDL_FRect untuk rendering
    int speed;             // Kecepatan mobil
} Car;

void initCar(Car* car, float x, float y, float w, float h, int speed);
void moveLeft(Car* car);
void moveRight(Car* car, int screenWidth);
void renderCar(SDL_Renderer* renderer, Car* car); // Render car using SDL_FRect

#endif // MOBIL_H
