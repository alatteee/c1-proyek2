#include "../include/menu.h"
#include <raylib.h>
#include "../include/config.h"
#include "../include/mobil.h"
#include "../include/skor.h"
#include "../include/rintangan.h"

void DrawMenu(int selectedOption, Texture2D brickTexture)
{
    const char *options[] = {"Start Game", "Music: On", "Exit Game"};
    const int NUM_OPTIONS = 3;
    const int optionSpacing = 60;
    const int boxPadding = 10;
    const int boxWidth = 200;
    const int boxHeight = 40;

    // Gambar latar belakang
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Perbarui teks opsi musik
    const char *musicOption = isMusicEnabled ? "Music: On" : "Music: Off";
    options[1] = musicOption;

    // Gambar opsi menu
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2;
        int boxY = 300 + i * optionSpacing;
        Color boxColor = (i == selectedOption) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);

        const char *text = options[i];
        int textWidth = MeasureText(text, 20);
        int textX = boxX + (boxWidth - textWidth) / 2;
        int textY = boxY + boxPadding;
        DrawText(text, textX, textY, 20, BLACK);
    }
}

void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor)
{
    const int NUM_OPTIONS = 3;

    if (IsKeyPressed(KEY_UP))
    {
        (*selectedOption)--;
        if (*selectedOption < 0)
            *selectedOption = NUM_OPTIONS - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        (*selectedOption)++;
        if (*selectedOption >= NUM_OPTIONS)
            *selectedOption = 0;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (*selectedOption)
        {
        case 0: // Start Game
            *gameState = STATE_LEVEL_MENU;
            break;
        case 1: // Music: On/Off
            isMusicEnabled = !isMusicEnabled;
            if (isMusicEnabled)
                PlayMusicStream(menuMusic);
            else
                StopMusicStream(menuMusic);
            break;
        case 2: // Exit Game
            *gameState = STATE_EXIT;
            break;
        }
    }
}

void DrawLevelMenu(int selectedLevel, Texture2D brickTexture)
{
    // Gambar latar belakang
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "Select Level";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar opsi level
    for (int i = 0; i < NUM_LEVELS; i++)
    {
        int boxX = SCREEN_WIDTH / 2 - 100;
        int boxY = 350 + i * 60;
        Color boxColor = (i == selectedLevel) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, 200, 50, boxColor);
        DrawText(levels[i].name, boxX + 10, boxY + 10, 20, BLACK);
    }
}

void handleLevelMenuInput(int *selectedLevel, GameState *gameState)
{
    if (IsKeyPressed(KEY_UP))
    {
        (*selectedLevel)--;
        if (*selectedLevel < 0)
            *selectedLevel = NUM_LEVELS - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        (*selectedLevel)++;
        if (*selectedLevel >= NUM_LEVELS)
            *selectedLevel = 0;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        *gameState = STATE_INPUT_NAME; // Pindah ke input nama
    }
}

void DrawInputName(char *playerName, Texture2D brickTexture)
{
    // Gambar latar belakang
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "Enter Your Name";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar input box
    int boxX = SCREEN_WIDTH / 2 - 100;
    int boxY = 350;
    DrawRectangle(boxX, boxY, 200, 50, LIGHTGRAY);
    DrawText(playerName, boxX + 10, boxY + 10, 20, BLACK);

    // Gambar instruksi
    const char *instruction = "Press ENTER to Continue";
    int instructionWidth = MeasureText(instruction, 20);
    int instructionX = SCREEN_WIDTH / 2 - instructionWidth / 2;
    int instructionY = 450;
    DrawText(instruction, instructionX, instructionY, 20, WHITE);
}