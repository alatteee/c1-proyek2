// level.h
#ifndef LEVEL_H
#define LEVEL_H

typedef struct LevelNode {
    char name[20];               // Nama level
    int obstacleSpeed;           // Kecepatan rintangan
    struct LevelNode* next;      // Pointer ke level selanjutnya
} LevelNode;

// Fungsi-fungsi
LevelNode* CreateLevelNode(const char* name, int speed);
void AppendLevel(LevelNode** head, const char* name, int speed);
void FreeLevels(LevelNode* head);
void PrintLevels(LevelNode* head);  // Untuk testing/debug
LevelNode* getLevelByIndex(LevelNode* head, int index);


#endif
