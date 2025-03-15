#ifndef MOBIL_H
#define MOBIL_H

#include <raylib.h>
#include "config.h"

typedef struct {
    float x;
    float y;
    float width;
    float height;
    Rectangle rect;
    int speed;
    bool isInvulnerable; // Apakah mobil sedang invulnerable
    float invulnerabilityTimer; // Timer untuk invulnerability
} Car;

void initCar(Car *car, float x, float y, float w, float h, int speed);
void moveLeft(Car *car);
void moveRight(Car *car, int screenWidth);
void renderCar(Car *car);
void handleCarInput(Car *cars);
void resetCarPosition(Car *car); // Reset posisi mobil
void updateCarInvulnerability(Car *car, float deltaTime); // Update invulnerability
bool checkCarCollision(Car *car, Rectangle obstacle); // Cek tabrakan

#endif // MOBIL_H