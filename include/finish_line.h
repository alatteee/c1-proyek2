#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include <raylib.h>
#include <stdbool.h>
#include "mobil.h"
#include "config.h"

typedef struct FinishTile {
    int x, y;
    Color color;
    struct FinishTile *next;
} FinishTile;

void InitFinishLine(void);
void DrawFinishLine(void);
bool CheckFinishLineCollision(Car *car);
void FreeFinishLine(void);

#endif
