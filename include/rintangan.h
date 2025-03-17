#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <stdbool.h>
#include <raylib.h>
#include "config.h"  // Make sure this contains definitions for SCREEN_WIDTH, SCREEN_HEIGHT, etc.

typedef struct Rintangan {
    float x, y;
    float width, height;
    int type;
    bool hasPassed;
    bool hasCollided; // Flag baru untuk menandai tabrakan
} Rintangan;

extern Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

void initRintangan();
void updateRintangan(/* Skor pointer and obstacleSpeed parameter as needed */);
int checkCollision(float x, float y, float width, float height);

// Add the declaration for drawRintangan()
void drawRintangan();

#endif // RINTANGAN_H