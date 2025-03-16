#include "../include/menu.h"
#include <raylib.h>
#include "../include/config.h"
#include "../include/mobil.h" 
#include "../include/skor.h"
#include "../include/rintangan.h"

void DrawMenu(int selectedOption, Texture2D brickTexture)
{
    const char *options[NUM_OPTIONS] = {"Start Game", "Select Level", "Exit"};
    const int optionSpacing = 60; // Jarak antar opsi
    const int boxPadding = 10;    // Padding di dalam kotak
    const int boxWidth = 200;     // Lebar kotak
    const int boxHeight = 40;     // Tinggi kotak

    // Gambar latar belakang tanpa animasi
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul di tengah layar
    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40);        // Hitung lebar teks judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X untuk teks judul
    int titleY = 250;                               // Posisi Y untuk teks judul
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar opsi menu dengan kotak teks di tengah layar
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        // Hitung posisi kotak
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2; // Posisi X untuk kotak (tengah layar)
        int boxY = 350 + i * optionSpacing;         // Posisi Y untuk kotak (dimulai dari 350, lebih ke bawah)

        // Warna kotak (berubah jika dipilih)
        Color boxColor = (i == selectedOption) ? RED : LIGHTGRAY;

        // Gambar kotak
        DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);

        // Gambar teks di dalam kotak
        const char *text = options[i];
        int textWidth = MeasureText(text, 20);         // Hitung lebar teks opsi
        int textX = boxX + (boxWidth - textWidth) / 2; // Posisi X untuk teks (tengah kotak)
        int textY = boxY + boxPadding;                 // Posisi Y untuk teks (dalam kotak)
        DrawText(text, textX, textY, 20, BLACK);
    }
}

// Fungsi untuk menangani input pada menu
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor)
{
    if (IsKeyPressed(KEY_UP))
    {
        (*selectedOption)--; 
        if (*selectedOption < 0)
            *selectedOption = NUM_OPTIONS - 1;  // Pastikan ini sesuai dengan jumlah pilihan menu
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
            for (int i = 0; i < NUM_CARS; i++)
            {
                initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
            }
            initRintangan(0);
            initSkor(skor);
            *lives = 3;
            *gameState = STATE_GAME;
            break;

        case 1: // Select Level
            *gameState = STATE_LEVEL_MENU; // Pindah ke menu level
            break;

        case 2: // Exit
            *gameState = STATE_EXIT;
            break;
        }
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        *gameState = STATE_EXIT;
    }
}

void DrawLevelMenu(int selectedLevel, Texture2D brickTexture) {
    // Gambar latar belakang
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul menu
    const char *title = "Select Level";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X tetap di tengah
    int titleY = 250; // Posisi Y judul sama seperti menu utama
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar opsi level
    for (int i = 0; i < NUM_LEVELS; i++) {
        int boxX = SCREEN_WIDTH / 2 - 100; // Posisi X tetap di tengah
        int boxY = 350 + i * 60; // Posisi Y kotak sama seperti menu utama
        Color boxColor = (i == selectedLevel) ? RED : LIGHTGRAY;

        DrawRectangle(boxX, boxY, 200, 50, boxColor);
        DrawText(levels[i].name, boxX + 10, boxY + 10, 20, BLACK);
    }
}

void handleLevelMenuInput(int *selectedLevel, GameState *gameState) {
    if (IsKeyPressed(KEY_UP)) {
        (*selectedLevel)--;
        if (*selectedLevel < 0) *selectedLevel = NUM_LEVELS - 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        (*selectedLevel)++;
        if (*selectedLevel >= NUM_LEVELS) *selectedLevel = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        initRintangan(*selectedLevel); // Inisialisasi ulang rintangan
        *gameState = STATE_GAME; // Pindah ke state game dengan level yang dipilih
    }
}