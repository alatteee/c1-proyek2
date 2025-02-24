#ifndef MOBIL_H
#define MOBIL_H

#include <SDL3/SDL.h>

// Structure for Car
typedef struct {
    int x;          // X position of the car
    int y;          // Y position of the car
    int width;      // Width of the car
    int height;     // Height of the car
    SDL_Rect rect; // SDL_Rect for rendering, synced with x, y, width, height
    int speed;
} Car;

void initCar(Car* car, int x, int y, int w, int h, int speed);
void moveLeft(Car* car);
void moveRight(Car* car, int screenWidth);

#endif // MOBIL_H
