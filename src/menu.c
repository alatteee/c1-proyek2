#include "menu.h"

// Fungsi untuk menggambar menu
void DrawMenu(int selectedOption)
{
    const char *options[NUM_OPTIONS] = {"Start Game", "Options", "Exit"};

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Gambar judul
    DrawText("C1 Brick Racer", 250, 100, 40, BLACK);

    // Gambar opsi menu
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        Color color = (i == selectedOption) ? RED : BLACK; // Warna teks berubah jika dipilih
        DrawText(options[i], 300, 200 + i * 50, 20, color);
    }

    EndDrawing();
}

// Fungsi untuk mengupdate menu berdasarkan input pengguna
int UpdateMenu(int selectedOption)
{
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedOption = (selectedOption + 1) % NUM_OPTIONS; // Pindah ke opsi berikutnya
    }
    if (IsKeyPressed(KEY_UP))
    {
        selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS; // Pindah ke opsi sebelumnya
    }
    return selectedOption;
}