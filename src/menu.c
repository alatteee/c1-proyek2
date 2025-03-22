#include "../include/menu.h"
#include <raylib.h>
#include "../include/config.h"
#include "../include/mobil.h"
#include "../include/skor.h"
#include "../include/rintangan.h"


// Fungsi untuk menggambar menu utama
void DrawMenu(int selectedOption, Texture2D brickTexture)
{
    const char *options[] = {"Start Game", "Music: On", "Exit Game"}; // Pilihan menu
    const int NUM_OPTIONS = 3; // Jumlah pilihan menu
    const int optionSpacing = 60; // Jarak antar pilihan menu
    const int boxPadding = 10;   // Padding dalam kotak menu
    const int boxWidth = 200;    // Lebar kotak pilihan menu
    const int boxHeight = 40;    // Tinggi kotak pilihan menu

    // Gambar latar belakang menggunakan tekstur brickTexture
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "C1 Brick Racer";
    int titleWidth = MeasureText(title, 40); // Mengukur lebar judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X agar judul di tengah layar
    int titleY = 250; // Posisi Y untuk judul
    DrawText(title, titleX, titleY, 40, WHITE); // Gambar teks judul di layar

    // Perbarui teks opsi musik (tampilkan "Music: On" atau "Music: Off")
    const char *musicOption = isMusicEnabled ? "Music: On" : "Music: Off";
    options[1] = musicOption;

    // Gambar pilihan menu
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        int boxX = SCREEN_WIDTH / 2 - boxWidth / 2; // Posisi X untuk kotak pilihan
        int boxY = 300 + i * optionSpacing; // Posisi Y untuk kotak pilihan dengan jarak antar pilihan
        Color boxColor = (i == selectedOption) ? RED : LIGHTGRAY; // Warna kotak berdasarkan pilihan yang dipilih

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor); // Gambar kotak pilihan menu

        const char *text = options[i]; // Ambil teks dari opsi menu
        int textWidth = MeasureText(text, 20); // Mengukur lebar teks
        int textX = boxX + (boxWidth - textWidth) / 2; // Posisi X agar teks di tengah kotak
        int textY = boxY + boxPadding; // Posisi Y untuk teks dalam kotak
        DrawText(text, textX, textY, 20, BLACK); // Gambar teks pilihan menu
    }
}

// Fungsi untuk menangani input dari menu utama
void handleMenuInput(int *selectedOption, GameState *gameState, Car cars[], int *lives, Skor *skor)
{
    const int NUM_OPTIONS = 3; // Jumlah pilihan menu

    if (IsKeyPressed(KEY_UP)) // Jika tombol arah atas ditekan
    {
        (*selectedOption)--; // Pilih opsi sebelumnya
        if (*selectedOption < 0)
            *selectedOption = NUM_OPTIONS - 1; // Jika mencapai opsi pertama, pilih opsi terakhir
    }
    if (IsKeyPressed(KEY_DOWN)) // Jika tombol arah bawah ditekan
    {
        (*selectedOption)++; // Pilih opsi berikutnya
        if (*selectedOption >= NUM_OPTIONS)
            *selectedOption = 0; // Jika mencapai opsi terakhir, pilih opsi pertama
    }

    if (IsKeyPressed(KEY_ENTER)) // Jika tombol Enter ditekan
    {
        switch (*selectedOption)
        {
        case 0: // Mulai permainan
            *gameState = STATE_LEVEL_MENU; // Pindah ke menu level
            break;
        case 1: // Opsi Musik: Aktifkan/Matiin musik
            isMusicEnabled = !isMusicEnabled; // Toggle status musik
            if (isMusicEnabled)
                PlayMusicStream(menuMusic); // Mainkan musik
            else
                StopMusicStream(menuMusic); // Hentikan musik
            break;
        case 2: // Keluar dari permainan
            *gameState = STATE_EXIT; // Set status permainan untuk keluar
            break;
        }
    }
}

// Fungsi untuk menggambar menu level
void DrawLevelMenu(int selectedLevel, Texture2D brickTexture)
{
    // Gambar latar belakang menggunakan tekstur brickTexture
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "Select Level";
    int titleWidth = MeasureText(title, 40); // Mengukur lebar judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X agar judul di tengah layar
    int titleY = 250; // Posisi Y untuk judul
    DrawText(title, titleX, titleY, 40, WHITE); // Gambar teks judul di layar

    // Gambar pilihan level
    for (int i = 0; i < NUM_LEVELS; i++)
    {
        int boxX = SCREEN_WIDTH / 2 - 100; // Posisi X untuk kotak level
        int boxY = 300 + i * 60; // Posisi Y untuk kotak level
        Color boxColor = (i == selectedLevel) ? RED : LIGHTGRAY; // Warna kotak berdasarkan level yang dipilih

        DrawRectangle(boxX, boxY, 200, 50, boxColor); // Gambar kotak pilihan level
        DrawText(levels[i].name, boxX + 10, boxY + 10, 20, BLACK); // Gambar nama level
    }
}

// Fungsi untuk menangani input dari menu level
void handleLevelMenuInput(int *selectedLevel, GameState *gameState)
{
    if (IsKeyPressed(KEY_UP)) // Jika tombol arah atas ditekan
    {
        (*selectedLevel)--; // Pilih level sebelumnya
        if (*selectedLevel < 0)
            *selectedLevel = NUM_LEVELS - 1; // Jika mencapai level pertama, pilih level terakhir
    }
    if (IsKeyPressed(KEY_DOWN)) // Jika tombol arah bawah ditekan
    {
        (*selectedLevel)++; // Pilih level berikutnya
        if (*selectedLevel >= NUM_LEVELS)
            *selectedLevel = 0; // Jika mencapai level terakhir, pilih level pertama
    }

    if (IsKeyPressed(KEY_ENTER)) // Jika tombol Enter ditekan
    {
        *gameState = STATE_INPUT_NAME; // Pindah ke menu input nama
    }
}

// Fungsi untuk menggambar menu input nama
void DrawInputName(char *playerName, Texture2D brickTexture)
{
    // Gambar latar belakang menggunakan tekstur brickTexture
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "Enter Your Name";
    int titleWidth = MeasureText(title, 40); // Mengukur lebar judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2; // Posisi X agar judul di tengah layar
    int titleY = 250; // Posisi Y untuk judul
    DrawText(title, titleX, titleY, 40, WHITE); // Gambar teks judul di layar

    // Gambar input box
    int boxX = SCREEN_WIDTH / 2 - 100; // Posisi X untuk kotak input nama
    int boxY = 350; // Posisi Y untuk kotak input nama
    DrawRectangle(boxX, boxY, 200, 50, LIGHTGRAY); // Gambar kotak input
    DrawText(playerName, boxX + 10, boxY + 10, 20, BLACK); // Gambar nama pemain yang telah dimasukkan

    // Gambar instruksi untuk melanjutkan
    const char *instruction = "Press ENTER to Continue";
    int instructionWidth = MeasureText(instruction, 20); // Mengukur lebar instruksi
    int instructionX = SCREEN_WIDTH / 2 - instructionWidth / 2; // Posisi X agar instruksi di tengah
    int instructionY = 450; // Posisi Y untuk instruksi
    DrawText(instruction, instructionX, instructionY, 20, WHITE); // Gambar instruksi
}