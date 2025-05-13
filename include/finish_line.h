#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include <raylib.h>
#include <stdbool.h>
#include "single_linked_list.h"
#include "mobil.h"
#include "config.h"

// Data satu kotak finish line
typedef struct {
    int   x, y;
    Color color;
} FinishTile;

// Buat list finish line (return List* yang udah diisi tile-tile)
List* InitFinishLine(void);

// Gambar semua tile di list, plus garis & teks FINISH
void DrawFinishLine(List* finishList);

// Cek tabrakan mobil sama garis finish
bool CheckFinishLineCollision(Car* car);

// Bebasin memori list + data tile-nya
void FreeFinishLine(List* finishList);

#endif // FINISH_LINE_H
