#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "config.h"
#include "mobil.h"
#include "level.h"
#include "skor.h"

// Forward declarations
typedef struct CarNode CarNode;

// Menu data structures
typedef struct {
    int selectedOption;
    Texture2D brickTexture;
} MainMenuData;

typedef struct {
    int selectedLevel;
    Texture2D brickTexture;
    LevelNode* levelList;
} LevelMenuData;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    Texture2D brickTexture;
} InputNameData;

typedef struct {
    int selectedCarIndex;
    Texture2D brickTexture;
    CarNode* carList;
} CarSelectionData;

typedef struct {
    Texture2D brickTexture;
} SettingsData;

// Menu node structure
typedef struct MenuNode {
    char title[50];
    GameState state;
    struct MenuNode* prev;
    struct MenuNode* next;
    void (*drawFunction)(void*);
    void (*handleInputFunction)(GameState*);
    void* data;
} MenuNode;

// Global variables
extern MenuNode* menuSystem;
extern MenuNode* currentMenu;
extern Music menuMusic;
extern bool isMusicEnabled;

// Function declarations
MenuNode* CreateMenuNode(const char* title, GameState state, 
                        void (*drawFunction)(void*), 
                        void (*handleInputFunction)(GameState*),
                        void* data);
void FreeMenu(MenuNode* head);
void AppendMenuNode(MenuNode** head, MenuNode* newNode);
void SetCurrentMenu(GameState state, MenuNode* menuSystem);
MenuNode* InitializeMenuSystem(Texture2D brickTexture, LevelNode* levelList, CarNode* carList);

// Menu drawing and input functions
void DrawMainMenu(void* data);
void HandleMainMenuInput(GameState* gameState);
void DrawLevelMenu(void* data);
void HandleLevelMenuInput(GameState* gameState);
void DrawInputNameMenu(void* data);
void HandleInputNameMenuInput(GameState* gameState);
void DrawCarSelectionMenu(void* data);
void HandleCarSelectionMenuInput(GameState* gameState);
void DrawSettingsMenu(void* data);
void HandleSettingsMenuInput(GameState* gameState);

#endif