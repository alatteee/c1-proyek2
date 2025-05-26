#ifndef LEVEL_H
#define LEVEL_H

#include "single_linked_list.h"

typedef struct {
    char name[20];               // Nama level
    int obstacleSpeed;           // Kecepatan rintangan
} LevelData;

// Fungsi-fungsi
List* createLevelList(void);
LevelData* createLevelData(const char* name, int speed);
void freeLevelData(void* data);
LevelData* getLevelByIndex(List* levelList, int index);
void freeLevelList(List* levelList);

#endif