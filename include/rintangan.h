#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <SDL3/SDL.h>

// Constants
#define MAX_LANES 3
#define MAX_OBSTACLES 5
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_CAR_WIDTH 40
#define PLAYER_CAR_HEIGHT 80

// Structure for obstacles
typedef struct {
    float x;
    float y;
    float width;
    float height;
    int type;  // 0: Rock (Circle), 1: Barrier (Triangle), 2: Car (Rectangle)
} Rintangan;

// Global variables
extern Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

// Function declarations
void initRintangan();
void drawCircle(SDL_Renderer *renderer, int x, int y, int r);
void drawTriangle(SDL_Renderer *renderer, int x, int y, int size);
void updateRintangan();
void drawRintangan(SDL_Renderer *renderer);
int checkCollision(float x, float y, float width, float height);

#endif /* RINTANGAN_H */