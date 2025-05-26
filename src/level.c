#include "../include/level.h"
#include <stdlib.h>
#include <string.h>

// Membuat data level baru
LevelData* createLevelData(const char* name, int speed) {
    LevelData* data = malloc(sizeof(LevelData));
    if (data) {
        strcpy(data->name, name);
        data->obstacleSpeed = speed;
    }
    return data;
}

// Membebaskan data level
void freeLevelData(void* data) {
    if (data) {
        free(data);
    }
}

// Membuat list level dengan data default
List* createLevelList(void) {
    List* levelList = buatList();
    
    tambahData(levelList, createLevelData("Easy", 3));
    tambahData(levelList, createLevelData("Medium", 5));
    tambahData(levelList, createLevelData("Hard", 7));
    
    return levelList;
}

// Mendapatkan level berdasarkan index
LevelData* getLevelByIndex(List* levelList, int index) {
    return (LevelData*)ambilData(levelList, index);
}

// Membebaskan seluruh list level
void freeLevelList(List* levelList) {
    hapusList(levelList, freeLevelData);
}