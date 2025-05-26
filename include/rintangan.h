#ifndef RINTANGAN_H
#define RINTANGAN_H

#include <stdbool.h>
#include <raylib.h>
#include "config.h"
#include "skor.h"
#include "double_linked_list.h"

// Struktur untuk menyimpan data obstacle
typedef struct {
    float x, y;
    float width, height;
    int type;
    bool hasPassed;
    bool hasCollided;
    Rectangle collisionBox;
    Texture2D texture;
} ObstacleData;

// Struktur untuk lane yang menggunakan linked list
typedef struct {
    DoubleList* obstacles;
    int obstacleCount;
    float nextSpawnTime;
} Lane;

// Variabel global untuk lanes
extern Lane lanes[MAX_LANES];
extern bool showCollisionBoxes;

// Function prototypes
void initRintangan();
void updateRintangan(Skor *skor, int obstacleSpeed);
void drawRintangan();
int checkCollision(float x, float y, float width, float height);
void freeRintangan();

// Toggle debug visualization
void toggleCollisionBoxVisibility();

// Resource management
void loadRintanganTextures();
void unloadRintanganTextures();

// Fungsi untuk node management
ObstacleData* createObstacleData(int laneIndex);
void addObstacleToLane(int laneIndex);
void removeObstacleFromLane(int laneIndex, DLNode* node);
void freeObstacleData(void* data);

// Fungsi untuk debug
void drawCollisionBoxes(bool drawPlayerBox, float x, float y, float width, float height);

#endif // RINTANGAN_H