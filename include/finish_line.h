#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include <raylib.h>
#include "config.h"
#include "mobil.h" // Untuk tipe Car

void DrawFinishLine();
bool CheckFinishLineCollision(Car *car);

#endif