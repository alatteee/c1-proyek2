#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "config.h"
#include "single_linked_list.h" 
#include "double_linked_list.h" // ADT List untuk level & mobil

extern DoubleList *menuList;

// Data untuk tiap jenis menu
typedef struct {
    int selectedOption;
    Texture2D brickTexture;
} MainMenuData;

typedef struct {
    int selectedLevel;
    Texture2D brickTexture;
    List* levelList;       // List<Level*>
} LevelMenuData;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    Texture2D brickTexture;
} InputNameData;

typedef struct {
    int selectedCarIndex;
    Texture2D brickTexture;
    List* carList;         // List<CarData*>
} CarSelectionData;

typedef struct {
    Texture2D brickTexture;
} SettingsData;

// Node doubly–linked untuk menu
typedef struct MenuNode {
    char title[50];
    GameState state;
    struct MenuNode* prev;
    struct MenuNode* next;
    void (*drawFunction)(void*);
    void (*handleInputFunction)(GameState*);
    void* data;
} MenuNode;

// Globals
extern MenuNode* menuSystem;
extern MenuNode* currentMenu;
extern Music menuMusic;
extern bool isMusicEnabled;

// Lifecycle menu
void InitializeMenuSystem(Texture2D brickTexture, List* levelList, List* carList);

void FreeMenuSystem(void);

// Membuat / merangkai node
MenuNode* CreateMenuNode(const char* title, GameState state,
                         void (*drawFunction)(void*),
                         void (*handleInputFunction)(GameState*),
                         void* data);
void AppendMenuNode(MenuNode** head, MenuNode* node);
void FreeMenu(MenuNode* head);

// Navigasi menu
void SetCurrentMenu(GameState state);
void HandleMenuInput(GameState *state);
void DrawMenu(void);

// Draw & input per-submenu
void DrawMainMenu(void* data);
void HandleMainMenuInput(GameState* state);
void DrawLevelMenu(void* data);
void HandleLevelMenuInput(GameState* state);
void DrawInputNameMenu(void* data);
void HandleInputNameMenuInput(GameState* state);
void DrawCarSelectionMenu(void* data);
void HandleCarSelectionMenuInput(GameState* state);
void DrawSettingsMenu(void* data);
void HandleSettingsMenuInput(GameState* state);

#endif // MENU_H
