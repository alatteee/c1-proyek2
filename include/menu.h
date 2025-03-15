#ifndef MENU_H
#define MENU_H

#include "raylib.h"

#define NUM_OPTIONS 3

// Deklarasi fungsi DrawMenu dengan parameter Texture2D saja (brickOffset dihapus)
void DrawMenu(int selectedOption, Texture2D brickTexture);

#endif