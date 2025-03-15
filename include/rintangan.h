#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <raylib.h>
#include "config.h"

// Constants for rintangan
#define MAX_LANES 3
#define MAX_OBSTACLES 5

// Structure for obstacles
typedef struct {
    float x;
    float y;
    float width;
    float height;
    int type;  // 0: Cat, 1: Rock, 2: Car, 3: Dog
} Rintangan;

// Global variables
extern Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

// Function declarations
void initRintangan();
void updateRintangan();
void drawRintangan();
int checkCollision(float x, float y, float width, float height);

#endif