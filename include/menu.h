#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "config.h"
#include "mobil.h"
#include "level.h"
#include "skor.h"

// Mendeklarasikan variabel global menuMusic untuk musik latar menu
extern Music menuMusic;
// Mendeklarasikan variabel global isMusicEnabled untuk menandakan apakah musik diaktifkan
extern bool isMusicEnabled;

// Deklarasi fungsi untuk menggambar menu utama permainan
void DrawMenu(int selectedOption, Texture2D brickTexture);
// Deklarasi fungsi untuk menangani input dari menu utama
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor);

// Deklarasi fungsi untuk menggambar menu pemilihan level
void DrawLevelMenu(int selectedLevel, Texture2D brickTexture, List *levelList);

// Deklarasi fungsi untuk menangani input dari menu pemilihan level
void handleLevelMenuInput(int *selectedLevel, GameState *gameState, List *levelList);

// Deklarasi fungsi untuk menggambar menu input nama pemain
void DrawInputName(char *playerName, Texture2D brickTexture);

// Deklarasi fungsi untuk settings menu
void DrawSettingsMenu(int selectedOption, Texture2D brickTexture);
void handleSettingsInput(int *selectedOption, GameState *gameState);

#endif