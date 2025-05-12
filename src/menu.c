#include "../include/menu.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mobil.h"
#include "../include/skor.h"
#include "../include/rintangan.h"
#include "../include/level.h"
#include "../include/mobil_selection.h"

// Struktur data untuk menu utama
typedef struct
{
    int selectedOption;
    Texture2D brickTexture;
} MainMenuData;

// Struktur data untuk menu level
typedef struct
{
    int selectedLevel;
    Texture2D brickTexture;
    LevelNode *levelList;
} LevelMenuData;

// Struktur data untuk menu input nama
typedef struct
{
    char playerName[MAX_NAME_LENGTH];
    Texture2D brickTexture;
} InputNameData;

// Struktur data untuk menu pemilihan mobil
typedef struct
{
    int selectedCarIndex;
    Texture2D brickTexture;
    CarNode *carList;
} CarSelectionData;

// Struktur data untuk menu settings
typedef struct
{
    Texture2D brickTexture;
} SettingsData;

// Implementasi fungsi untuk membuat node menu baru
MenuNode *CreateMenuNode(const char *title, GameState state,
                         void (*drawFunction)(void *),
                         void (*handleInputFunction)(GameState *),
                         void *data)
{
    MenuNode *newNode = (MenuNode *)malloc(sizeof(MenuNode));
    if (newNode == NULL)
    {
        return NULL;
    }

    strncpy(newNode->title, title, sizeof(newNode->title));
    newNode->state = state;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->drawFunction = drawFunction;
    newNode->handleInputFunction = handleInputFunction;
    newNode->data = data;

    return newNode;
}

// Implementasi fungsi untuk membebaskan memori menu
void FreeMenu(MenuNode *head)
{
    MenuNode *current = head;
    while (current != NULL)
    {
        MenuNode *next = current->next;
        if (current->data != NULL)
        {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

// Implementasi fungsi untuk menambahkan node menu
void AppendMenuNode(MenuNode **head, MenuNode *newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    MenuNode *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

// Implementasi fungsi untuk menggambar menu utama
void DrawMainMenu(void *data)
{
    MainMenuData *menuData = (MainMenuData *)data;
    const char *options[] = {"Start Game", "Settings", "Exit Game"};
    const int NUM_OPTIONS = 3;
    const int optionSpacing = 60;
    const int boxPadding = 10;
    const int boxWidth = 200;
    const int boxHeight = 40;

    DrawTexture(menuData->brickTexture, 0, 0, WHITE);

    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2;
        int boxY = 300 + i * optionSpacing;
        Color boxColor = (i == menuData->selectedOption) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);
        const char *text = options[i];
        int textWidth = MeasureText(text, 20);
        int textX = boxX + (boxWidth - textWidth) / 2;
        int textY = boxY + boxPadding;
        DrawText(text, textX, textY, 20, BLACK);
    }
}

// Implementasi fungsi untuk menangani input menu utama
void HandleMainMenuInput(GameState *gameState)
{
    MainMenuData *menuData = (MainMenuData *)(*gameState == STATE_MENU ? currentMenu->data : NULL);
    if (menuData == NULL)
        return;

    const int NUM_OPTIONS = 3;

    if (IsKeyPressed(KEY_UP))
    {
        menuData->selectedOption--;
        if (menuData->selectedOption < 0)
            menuData->selectedOption = NUM_OPTIONS - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        menuData->selectedOption++;
        if (menuData->selectedOption >= NUM_OPTIONS)
            menuData->selectedOption = 0;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (menuData->selectedOption)
        {
        case 0:
            *gameState = STATE_LEVEL_MENU;
            break;
        case 1:
            *gameState = STATE_SETTINGS;
            break;
        case 2:
            *gameState = STATE_EXIT;
            break;
        }
    }
}

// Implementasi fungsi untuk menggambar menu level
void DrawLevelMenu(void *data)
{
    LevelMenuData *levelData = (LevelMenuData *)data;
    DrawTexture(levelData->brickTexture, 0, 0, WHITE);

    const char *title = "Select Level";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    LevelNode *current = levelData->levelList;
    int i = 0;

    while (current != NULL)
    {
        int boxX = SCREEN_WIDTH / 2 - 100;
        int boxY = 300 + i * 60;
        Color boxColor = (i == levelData->selectedLevel) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, 200, 50, boxColor);
        DrawText(current->name, boxX + 10, boxY + 10, 20, BLACK);

        current = current->next;
        i++;
    }

    // Draw back option
    int backBoxY = 300 + i * 60;
    DrawRectangle(SCREEN_WIDTH / 2 - 100, backBoxY, 200, 50, LIGHTGRAY);
    DrawText("Back", SCREEN_WIDTH / 2 - MeasureText("Back", 20) / 2, backBoxY + 15, 20, BLACK);
}

// Implementasi fungsi untuk menangani input menu level
void HandleLevelMenuInput(GameState *gameState)
{
    LevelMenuData *levelData = (LevelMenuData *)(*gameState == STATE_LEVEL_MENU ? currentMenu->data : NULL);
    if (levelData == NULL)
        return;

    int numLevels = 0;
    LevelNode *temp = levelData->levelList;
    while (temp != NULL)
    {
        numLevels++;
        temp = temp->next;
    }

    if (IsKeyPressed(KEY_UP))
    {
        levelData->selectedLevel--;
        if (levelData->selectedLevel < -1) // -1 untuk opsi back
            levelData->selectedLevel = numLevels - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        levelData->selectedLevel++;
        if (levelData->selectedLevel >= numLevels)
            levelData->selectedLevel = -1; // -1 untuk opsi back
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (levelData->selectedLevel == -1)
        {
            *gameState = STATE_MENU;
        }
        else
        {
            *gameState = STATE_INPUT_NAME;
        }
    }
}

// Implementasi fungsi untuk menggambar menu input nama
void DrawInputNameMenu(void *data)
{
    InputNameData *inputData = (InputNameData *)data;
    DrawTexture(inputData->brickTexture, 0, 0, WHITE);

    const char *title = "Enter Your Name";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    int boxX = SCREEN_WIDTH / 2 - 100;
    int boxY = 350;
    DrawRectangle(boxX, boxY, 200, 50, LIGHTGRAY);
    DrawText(inputData->playerName, boxX + 10, boxY + 10, 20, BLACK);

    const char *instruction = "Press ENTER to Continue, ESC to Go Back";
    int instructionWidth = MeasureText(instruction, 20);
    int instructionX = SCREEN_WIDTH / 2 - instructionWidth / 2;
    int instructionY = 450;
    DrawText(instruction, instructionX, instructionY, 20, WHITE);
}

// Implementasi fungsi untuk menangani input menu input nama
void HandleInputNameMenuInput(GameState *gameState)
{
    InputNameData *inputData = (InputNameData *)(*gameState == STATE_INPUT_NAME ? currentMenu->data : NULL);
    if (inputData == NULL)
        return;

    int key = GetCharPressed();
    if (key > 0 && strlen(inputData->playerName) < MAX_NAME_LENGTH - 1)
    {
        inputData->playerName[strlen(inputData->playerName)] = (char)key;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputData->playerName) > 0)
    {
        inputData->playerName[strlen(inputData->playerName) - 1] = '\0';
    }
    if (IsKeyPressed(KEY_ENTER) && strlen(inputData->playerName) > 0)
    {
        *gameState = STATE_SELECT_CAR;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        *gameState = STATE_LEVEL_MENU;
    }
}

// Implementasi fungsi untuk menggambar menu pemilihan mobil
void DrawCarSelectionMenu(void *data)
{
    CarSelectionData *carData = (CarSelectionData *)data;
    DrawTexture(carData->brickTexture, 0, 0, WHITE);

    const char *title = "Select Your Car";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 150;
    DrawText(title, titleX, titleY, 40, WHITE);

    CarNode *current = carData->carList;
    int i = 0;
    int startY = 250;

    while (current != NULL)
    {
        int boxX = SCREEN_WIDTH / 2 - 150;
        int boxY = startY + i * 120;
        Color boxColor = (i == carData->selectedCarIndex) ? RED : LIGHTGRAY;

        // Draw car selection box
        DrawRectangle(boxX, boxY, 300, 100, boxColor);

        // Draw car preview
        DrawTexture(current->car.texture, boxX + 10, boxY + 10, WHITE);

        // Draw car name
        DrawText(current->name, boxX + 120, boxY + 40, 20, BLACK);

        current = current->next;
        i++;
    }

    // Draw back option
    int backBoxY = startY + i * 120;
    DrawRectangle(SCREEN_WIDTH / 2 - 100, backBoxY, 200, 50, LIGHTGRAY);
    DrawText("Back", SCREEN_WIDTH / 2 - MeasureText("Back", 20) / 2, backBoxY + 15, 20, BLACK);
}

// Implementasi fungsi untuk menangani input menu pemilihan mobil
void HandleCarSelectionMenuInput(GameState *gameState)
{
    CarSelectionData *carData = (CarSelectionData *)(*gameState == STATE_SELECT_CAR ? currentMenu->data : NULL);
    if (carData == NULL)
        return;

    int totalCars = countCars(carData->carList);

    if (IsKeyPressed(KEY_UP))
    {
        carData->selectedCarIndex--;
        if (carData->selectedCarIndex < -1) // -1 untuk opsi back
            carData->selectedCarIndex = totalCars - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        carData->selectedCarIndex++;
        if (carData->selectedCarIndex >= totalCars)
            carData->selectedCarIndex = -1; // -1 untuk opsi back
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (carData->selectedCarIndex == -1)
        {
            *gameState = STATE_INPUT_NAME;
        }
        else
        {
            *gameState = STATE_GAME;
        }
    }
}

// Implementasi fungsi untuk menggambar menu settings
void DrawSettingsMenu(void *data)
{
    SettingsData *settingsData = (SettingsData *)data;
    DrawTexture(settingsData->brickTexture, 0, 0, WHITE);

    const char *title = "Settings";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Music option
    const char *musicOption = isMusicEnabled ? "Music: On" : "Music: Off";
    int boxX = SCREEN_WIDTH / 2 - 100;
    int boxY = 350;
    DrawRectangle(boxX, boxY, 200, 50, LIGHTGRAY);
    DrawText(musicOption, boxX + (200 - MeasureText(musicOption, 20)) / 2, boxY + 15, 20, BLACK);

    // Back option
    boxY += 80;
    DrawRectangle(boxX, boxY, 200, 50, LIGHTGRAY);
    DrawText("Back", SCREEN_WIDTH / 2 - MeasureText("Back", 20) / 2, boxY + 15, 20, BLACK);
}

// Implementasi fungsi untuk menangani input menu settings
void HandleSettingsMenuInput(GameState *gameState)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        isMusicEnabled = !isMusicEnabled;
        if (isMusicEnabled)
            PlayMusicStream(menuMusic);
        else
            StopMusicStream(menuMusic);
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        *gameState = STATE_MENU;
    }
}

// Inisialisasi sistem menu
MenuNode *InitializeMenuSystem(Texture2D brickTexture, LevelNode *levelList, CarNode *carList)
{
    MenuNode *head = NULL;

    // Buat data untuk setiap menu
    MainMenuData *mainMenuData = (MainMenuData *)malloc(sizeof(MainMenuData));
    mainMenuData->selectedOption = 0;
    mainMenuData->brickTexture = brickTexture;

    LevelMenuData *levelMenuData = (LevelMenuData *)malloc(sizeof(LevelMenuData));
    levelMenuData->selectedLevel = 0;
    levelMenuData->brickTexture = brickTexture;
    levelMenuData->levelList = levelList;

    InputNameData *inputNameData = (InputNameData *)malloc(sizeof(InputNameData));
    memset(inputNameData->playerName, 0, MAX_NAME_LENGTH);
    inputNameData->brickTexture = brickTexture;

    CarSelectionData *carSelectionData = (CarSelectionData *)malloc(sizeof(CarSelectionData));
    carSelectionData->selectedCarIndex = 0;
    carSelectionData->brickTexture = brickTexture;
    carSelectionData->carList = carList;

    SettingsData *settingsData = (SettingsData *)malloc(sizeof(SettingsData));
    settingsData->brickTexture = brickTexture;

    // Buat node untuk setiap menu
    MenuNode *mainMenu = CreateMenuNode("Main Menu", STATE_MENU, DrawMainMenu, HandleMainMenuInput, mainMenuData);
    MenuNode *levelMenu = CreateMenuNode("Level Menu", STATE_LEVEL_MENU, DrawLevelMenu, HandleLevelMenuInput, levelMenuData);
    MenuNode *inputNameMenu = CreateMenuNode("Input Name", STATE_INPUT_NAME, DrawInputNameMenu, HandleInputNameMenuInput, inputNameData);
    MenuNode *carSelectionMenu = CreateMenuNode("Car Selection", STATE_SELECT_CAR, DrawCarSelectionMenu, HandleCarSelectionMenuInput, carSelectionData);
    MenuNode *settingsMenu = CreateMenuNode("Settings", STATE_SETTINGS, DrawSettingsMenu, HandleSettingsMenuInput, settingsData);

    // Susun menu dalam double linked list
    AppendMenuNode(&head, mainMenu);
    AppendMenuNode(&head, levelMenu);
    AppendMenuNode(&head, inputNameMenu);
    AppendMenuNode(&head, carSelectionMenu);
    AppendMenuNode(&head, settingsMenu);

    return head;
}

// Variabel global untuk menu saat ini
MenuNode *currentMenu = NULL;
MenuNode *menuSystem = NULL;

// Fungsi untuk mengubah menu saat ini
void SetCurrentMenu(GameState state, MenuNode *menuSystem)
{
    MenuNode *current = menuSystem;
    while (current != NULL)
    {
        if (current->state == state)
        {
            currentMenu = current;
            return;
        }
        current = current->next;
    }
    currentMenu = menuSystem; // Default ke menu utama jika tidak ditemukan
}