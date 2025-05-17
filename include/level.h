#ifndef LEVEL_H
#define LEVEL_H

#include "single_linked_list.h"

#define MAX_LEVEL_NAME_LENGTH 20

typedef struct {
    char name[32];
    int obstacleSpeed;
} Level;

// ADT List dipakai untuk level
void AppendLevel(List *list, const char *name, int speed);
Level* getLevelByIndex(List *list, int index);

// Buat list level kosong
List* CreateLevelList(void);

// Ambil pointer ke Level pada index (0-based), atau NULL jika out-of-range
Level* getLevelByIndex(List* list, int index);

List *LoadDefaultLevels(void);

// Bebaskan semua node + data level
void FreeLevels(List* list);

#endif // LEVEL_H
