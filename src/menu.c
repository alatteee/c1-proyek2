#include "menu.h"
#include <raylib.h>
#include "config.h" // Pastikan ini di-include

void DrawMenu(int selectedOption, Texture2D brickTexture, float brickOffset)
{
    const char *options[NUM_OPTIONS] = {"Start Game", "Options", "Exit"};
    const int optionSpacing = 60; // Jarak antar opsi
    const int boxPadding = 10;    // Padding di dalam kotak
    const int boxWidth = 200;     // Lebar kotak
    const int boxHeight = 40;     // Tinggi kotak

    // Gambar animasi brick bergerak sebagai latar belakang
    for (int y = -brickTexture.height; y < SCREEN_HEIGHT; y += brickTexture.height)
    {
        for (int x = -brickOffset; x < SCREEN_WIDTH; x += brickTexture.width)
        {
            DrawTexture(brickTexture, x, y, WHITE);
        }
    }

    // Gambar judul di tengah layar
    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40);        // Hitung lebar teks judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X untuk teks judul
    int titleY = 100;                               // Posisi Y untuk teks judul
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar opsi menu dengan kotak teks di tengah layar
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        // Hitung posisi kotak
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2; // Posisi X untuk kotak (tengah layar)
        int boxY = 200 + i * optionSpacing;         // Posisi Y untuk kotak

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