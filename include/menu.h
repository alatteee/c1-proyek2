#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "config.h"
#include "mobil.h"
#include "skor.h"

// Deklarasikan menuMusic sebagai extern
extern Music menuMusic;
extern bool isMusicEnabled;

void DrawMenu(int selectedOption, Texture2D brickTexture);
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor); // Hapus parameter yang tidak digunakan
void DrawLevelMenu(int selectedLevel, Texture2D brickTexture);
void handleLevelMenuInput(int *selectedLevel, GameState *gameState);
void DrawInputName(char *playerName, Texture2D brickTexture);

#endif