#ifndef MENU_H
#define MENU_H

#include "raylib.h"

#define NUM_OPTIONS 3

// Deklarasi fungsi DrawMenu dengan parameter tambahan Texture2D dan brickOffset
void DrawMenu(int selectedOption, Texture2D brickTexture, float brickOffset);

#endif