#include "../include/menu.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // FIXED: Tambahkan include stdio.h untuk snprintf
#include "../include/config.h"
#include "../include/mobil.h"
#include "../include/skor.h"
#include "../include/rintangan.h"
#include "../include/level.h"

// Implementasi menu utama (kembali ke original - tanpa linked list)
void DrawMenu(int selectedOption, Texture2D brickTexture) {
    const char *options[] = {"Start Game", "Leaderboard", "Settings", "Exit Game"};
    const int NUM_OPTIONS = 4;
    const int optionSpacing = 60;
    const int boxPadding = 10;
    const int boxWidth = 200;
    const int boxHeight = 40;

    DrawTexture(brickTexture, 0, 0, WHITE);

    // Draw title
    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 200;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Draw menu options
    for (int i = 0; i < NUM_OPTIONS; i++) {
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2;
        int boxY = 280 + i * optionSpacing;
        Color boxColor = (i == selectedOption) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);

        const char *text = options[i];
        int textWidth = MeasureText(text, 20);
        int textX = boxX + (boxWidth - textWidth) / 2;
        int textY = boxY + boxPadding;
        DrawText(text, textX, textY, 20, BLACK);
    }

    // Draw navigation instructions
    DrawText("Use UP/DOWN to navigate, ENTER to select",
             SCREEN_WIDTH / 2 - MeasureText("Use UP/DOWN to navigate, ENTER to select", 20) / 2,
             500, 20, WHITE);
}

// FIXED: Handle unused parameter warnings dengan (void) cast
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor) {
    // Suppress unused parameter warnings
    (void)cars;
    (void)lives;
    (void)skor;
    
    const int NUM_OPTIONS = 4;

    if (IsKeyPressed(KEY_UP)) {
        (*selectedOption)--;
        if (*selectedOption < 0)
            *selectedOption = NUM_OPTIONS - 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        (*selectedOption)++;
        if (*selectedOption >= NUM_OPTIONS)
            *selectedOption = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        switch (*selectedOption) {
        case 0:
            *gameState = STATE_LEVEL_MENU;
            break;
        case 1:
            *gameState = STATE_HIGH_SCORES;
            break;
        case 2:
            *gameState = STATE_SETTINGS;
            break;
        case 3:
            *gameState = STATE_EXIT;
            break;
        }
    }
}

// Settings menu (original implementation)
void DrawSettingsMenu(int selectedOption, Texture2D brickTexture) {
    const char *musicOption = isMusicEnabled ? "Music: ON" : "Music: OFF";
    const char *options[] = {musicOption, "Back to Menu"};
    const int NUM_OPTIONS = 2;
    const int optionSpacing = 60;
    const int boxPadding = 10;
    const int boxWidth = 200;
    const int boxHeight = 40;

    DrawTexture(brickTexture, 0, 0, WHITE);

    const char *title = "Settings";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    for (int i = 0; i < NUM_OPTIONS; i++) {
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

    DrawText("Use UP/DOWN to navigate, ENTER to select",
             SCREEN_WIDTH / 2 - MeasureText("Use UP/DOWN to navigate, ENTER to select", 20) / 2,
             480, 20, WHITE);
}

void handleSettingsInput(int *selectedOption, GameState *gameState) {
    const int NUM_OPTIONS = 2;

    if (IsKeyPressed(KEY_UP)) {
        (*selectedOption)--;
        if (*selectedOption < 0)
            *selectedOption = NUM_OPTIONS - 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        (*selectedOption)++;
        if (*selectedOption >= NUM_OPTIONS)
            *selectedOption = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        switch (*selectedOption) {
        case 0:
            isMusicEnabled = !isMusicEnabled;
            if (isMusicEnabled)
                PlayMusicStream(menuMusic);
            else
                StopMusicStream(menuMusic);
            break;
        case 1:
            *gameState = STATE_MENU;
            break;
        }
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        *gameState = STATE_MENU;
    }
}

// Level menu - TERHUBUNG dengan single linked list level system
void DrawLevelMenu(int selectedLevel, Texture2D brickTexture, List *levelList) {
    DrawTexture(brickTexture, 0, 0, WHITE);

    const char *title = "Select Level";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 200;
    DrawText(title, titleX, titleY, 40, WHITE);

    // Menggunakan data dari single linked list levelList
    int levelCount = ukuranList(levelList);
    
    for (int i = 0; i < levelCount; i++) {
        LevelData *levelData = (LevelData*)ambilData(levelList, i);
        if (levelData) {
            int boxX = SCREEN_WIDTH / 2 - 100;
            int boxY = 280 + i * 70;
            Color boxColor = (i == selectedLevel) ? RED : LIGHTGRAY;

            DrawRectangle(boxX, boxY, 200, 50, boxColor);
            
            // Gambar nama level di tengah box
            int textWidth = MeasureText(levelData->name, 24);
            int textX = boxX + (200 - textWidth) / 2;
            int textY = boxY + 13;
            DrawText(levelData->name, textX, textY, 24, BLACK);
            
            // Gambar info kecepatan (snprintf sudah include stdio.h)
            char speedInfo[50];
            snprintf(speedInfo, sizeof(speedInfo), "Speed: %d", levelData->obstacleSpeed);
            int speedWidth = MeasureText(speedInfo, 16);
            int speedX = boxX + (200 - speedWidth) / 2;
            int speedY = boxY + 35;
            DrawText(speedInfo, speedX, speedY, 16, DARKGRAY);
        }
    }
    
    // Tambahkan instruksi navigation
    const char *instruction = "Use UP/DOWN to navigate, ENTER to select, ESC to go back";
    int instructionWidth = MeasureText(instruction, 18);
    DrawText(instruction, SCREEN_WIDTH / 2 - instructionWidth / 2, 500, 18, WHITE);
}

// FIXED: Sesuaikan dengan signature di header file
void handleLevelMenuInput(int *selectedLevel, GameState *gameState, List *levelList) {
    // Gunakan ukuran dari single linked list untuk bounds checking
    int totalLevels = ukuranList(levelList);
    
    if (IsKeyPressed(KEY_UP)) {
        (*selectedLevel)--;
        if (*selectedLevel < 0)
            *selectedLevel = totalLevels - 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        (*selectedLevel)++;
        if (*selectedLevel >= totalLevels)
            *selectedLevel = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        *gameState = STATE_INPUT_NAME;
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        *gameState = STATE_MENU;
    }
}

// Input name menu (original implementation)
void DrawInputName(char *playerName, Texture2D brickTexture) {
    DrawTexture(brickTexture, 0, 0, WHITE);

    const char *title = "Enter Your Name";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 250;
    DrawText(title, titleX, titleY, 40, WHITE);

    const char *subtitle = "Name:";
    int subtitleWidth = MeasureText(subtitle, 30);
    int subtitleX = SCREEN_WIDTH / 2 - subtitleWidth / 2;
    int subtitleY = 320;
    DrawText(subtitle, subtitleX, subtitleY, 30, WHITE);

    // Input box
    int boxX = SCREEN_WIDTH / 2 - 150;
    int boxY = 360;
    int boxWidth = 300;
    int boxHeight = 50;
    
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, WHITE);
    
    // Player name text
    DrawText(playerName, boxX + 15, boxY + 15, 24, BLACK);
    
    // Cursor blink effect
    static float blinkTimer = 0.0f;
    blinkTimer += GetFrameTime();
    if (((int)(blinkTimer * 2)) % 2 == 0) {
        int nameWidth = MeasureText(playerName, 24);
        DrawText("_", boxX + 15 + nameWidth, boxY + 15, 24, BLACK);
    }

    // Instructions
    const char *instruction1 = "Type your name and press ENTER to continue";
    int instruction1Width = MeasureText(instruction1, 20);
    int instruction1X = SCREEN_WIDTH / 2 - instruction1Width / 2;
    int instruction1Y = 450;
    DrawText(instruction1, instruction1X, instruction1Y, 20, WHITE);
    
    const char *instruction2 = "Press BACKSPACE to delete characters";
    int instruction2Width = MeasureText(instruction2, 16);
    int instruction2X = SCREEN_WIDTH / 2 - instruction2Width / 2;
    int instruction2Y = 480;
    DrawText(instruction2, instruction2X, instruction2Y, 16, GRAY);
}