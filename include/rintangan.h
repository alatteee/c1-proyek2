#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <SDL3/SDL.h>
#include "config.h"

#define MAX_LANES 3     // Jumlah jalur
#define MAX_OBSTACLES 5 // Jumlah maksimum rintangan per jalur

typedef struct
{
  int x, y, width, height;
  int type;
} Rintangan;

extern Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

void initRintangan();
void updateRintangan();
void drawRintangan(SDL_Renderer *renderer);
bool checkCollision(int carX, int carY, int carWidth, int carHeight);

#endif