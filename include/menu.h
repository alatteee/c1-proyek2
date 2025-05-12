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

// Struktur node untuk menu double linked list
typedef struct MenuNode
{
    char title[50];
    GameState state;
    struct MenuNode *prev;
    struct MenuNode *next;
    void (*drawFunction)(void *);
    void (*handleInputFunction)(GameState *);
    void *data;
} MenuNode;

// Fungsi untuk membuat node menu baru
MenuNode *CreateMenuNode(const char *title, GameState state,
                         void (*drawFunction)(void *),
                         void (*handleInputFunction)(GameState *),
                         void *data);

// Fungsi untuk membebaskan memori menu
void FreeMenu(MenuNode *head);

// Fungsi untuk menambahkan node menu
void AppendMenuNode(MenuNode **head, MenuNode *newNode);

// Deklarasi fungsi untuk menggambar menu utama permainan
void DrawMainMenu(void *data);
void HandleMainMenuInput(GameState *gameState);

// Deklarasi fungsi untuk menu level
void DrawLevelMenu(void *data);
void HandleLevelMenuInput(GameState *gameState);

// Deklarasi fungsi untuk menu input nama
void DrawInputNameMenu(void *data);
void HandleInputNameMenuInput(GameState *gameState);

// Deklarasi fungsi untuk menu pemilihan mobil
void DrawCarSelectionMenu(void *data);
void HandleCarSelectionMenuInput(GameState *gameState);

// Deklarasi fungsi untuk menu settings
void DrawSettingsMenu(void *data);
void HandleSettingsMenuInput(GameState *gameState);

// Inisialisasi menu
MenuNode *InitializeMenuSystem(Texture2D brickTexture, LevelNode *levelList, CarNode *carList);

#endif