#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "config.h"
#include "skor.h"
#include "mobil.h"

#define NUM_OPTIONS 3

// Hapus deklarasi renderMenu
void DrawMenu(int selectedOption, Texture2D brickTexture);
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor);

#endif