#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "config.h"
#include "skor.h"
#include "mobil.h"

#define NUM_OPTIONS 4
extern Music menuMusic; // Deklarasi eksternal
extern Music gameMusic; // Deklarasi eksternal
extern bool isMusicOn;

// Hapus deklarasi renderMenu
void DrawMenu(int selectedOption, Texture2D brickTexture);
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor);
void handleLevelMenuInput(int *selectedLevel, GameState *gameState);
void DrawLevelMenu(int selectedLevel, Texture2D brickTexture);

#endif