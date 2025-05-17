// include/rintangan.h
#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <stdbool.h>
#include <raylib.h>
#include "config.h"
#include "skor.h"
#include "double_linked_list.h"  // ADT double‐linked list

#define MAX_LANES 3
#define NUM_OBSTACLE_TYPES 6

// Data satu obstacle
typedef struct {
    float     x, y;
    float     width, height;
    int       type;
    bool      hasPassed;
    bool      hasCollided;
    Rectangle collisionBox;
    Texture2D texture;
} ObstacleData;

// Satu lane berisi list obstacle
typedef struct {
    DoubleList *obstacles;
    float       nextSpawnTime;
} Lane;

extern Lane lanes[MAX_LANES];
extern bool showCollisionBoxes;

void initRintangan(void);
void updateRintangan(Skor *skor, int obstacleSpeed);
void drawRintangan(void);
int  checkCollision(float x, float y, float width, float height);
void freeRintangan(void);

void toggleCollisionBoxVisibility(void);
void loadRintanganTextures(void);
void unloadRintanganTextures(void);

#endif // RINTANGAN_H
