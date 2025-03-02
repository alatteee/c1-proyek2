#ifndef MOBIL_H
#define MOBIL_H

#include <SDL3/SDL.h>

// Structure for Car
typedef struct {
    float x;               // X position of the car (float for SDL_FRect)
    float y;               // Y position of the car (float for SDL_FRect)
    float width;           // Width of the car (float for SDL_FRect)
    float height;          // Height of the car (float for SDL_FRect)
    SDL_FRect rect;        // SDL_FRect for rendering, synced with x, y, width, height
    int speed;
} Car;

void initCar(Car* car, float x, float y, float w, float h, int speed);
void moveLeft(Car* car);
void moveRight(Car* car, int screenWidth);
void renderCar(SDL_Renderer* renderer, Car* car); // Render car using SDL_FRect

#endif // MOBIL_H
