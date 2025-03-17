#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include "config.h"
#include "mobil.h"  // Include mobil.h to declare Car
#include <stdbool.h>

#define FINISH_LINE_Y 50        // Adjust value as needed
#define FINISH_LINE_HEIGHT 10   // Adjust value as needed

void DrawFinishLine(void);
bool CheckFinishLineCollision(Car *car);

#endif // FINISH_LINE_H