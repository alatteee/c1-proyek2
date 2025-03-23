#include "../include/high_score.h"
#include "../include/config.h"
#include <raylib.h>

// Fungsi untuk menyimpan skor tinggi ke dalam file
void SaveHighScore(const char *name, int score)
{
    HighScore highScores[MAX_HIGH_SCORES];  // Array untuk menyimpan daftar skor tinggi
    LoadHighScores(highScores);            // Memuat skor tinggi yang ada dari file

    // Cek apakah skor baru termasuk dalam daftar high score
    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        if (score > highScores[i].score)  // Jika skor baru lebih tinggi dari skor yang ada
        {
            // Geser skor yang ada untuk memberi ruang untuk skor baru
            for (int j = MAX_HIGH_SCORES - 1; j > i; j--)
            {
                strcpy(highScores[j].name, highScores[j - 1].name);  // Geser nama
                highScores[j].score = highScores[j - 1].score;        // Geser skor
            }
            // Simpan skor baru
            strcpy(highScores[i].name, name);  // Simpan nama pemain
            highScores[i].score = score;       // Simpan skor pemain
            break;  // Keluar dari loop setelah menyimpan skor
        }
    }

    // Simpan kembali daftar skor ke dalam file
    FILE *file = fopen("highscores.txt", "w");  // Buka file untuk menulis
    if (file)
    {
        // Tulis semua skor tinggi ke dalam file
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            fprintf(file, "%s %d\n", highScores[i].name, highScores[i].score);
        }
        fclose(file);  // Tutup file setelah menulis
    }
}

// Fungsi untuk memuat skor tinggi dari file
void LoadHighScores(HighScore highScores[])
{
    FILE *file = fopen("highscores.txt", "r");  // Buka file untuk membaca
    if (file)
    {
        // Baca nama dan skor dari file
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            fscanf(file, "%s %d", highScores[i].name, &highScores[i].score);
        }
        fclose(file);  // Tutup file setelah membaca
    }
    else
    {
        // Inisialisasi skor tinggi dengan nilai default jika file tidak ada
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            strcpy(highScores[i].name, "---");  // Nama default untuk pemain yang belum terdaftar
            highScores[i].score = 0;             // Skor default 0
        }
    }
}

// Fungsi untuk menggambar daftar skor tinggi di layar
void DrawHighScores(Texture2D brickTexture)
{
    HighScore highScores[MAX_HIGH_SCORES];  // Array untuk menyimpan daftar skor tinggi
    LoadHighScores(highScores);            // Memuat skor tinggi yang ada dari file

    // Gambar latar belakang menggunakan tekstur brickTexture
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul "High Scores"
    const char *title = "High Scores";
    int titleWidth = MeasureText(title, 40);  // Mengukur lebar teks judul
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;  // Posisi X agar judul berada di tengah
    int titleY = 200;  // Posisi Y untuk judul
    DrawText(title, titleX, titleY, 40, WHITE);  // Gambar teks judul di layar

    // Gambar daftar high score
    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        char scoreText[50];  // Array untuk menyimpan teks skor
        snprintf(scoreText, sizeof(scoreText), "%d. %s - %d", i + 1, highScores[i].name, highScores[i].score);  // Format teks skor
        int scoreWidth = MeasureText(scoreText, 20);  // Mengukur lebar teks skor
        int scoreX = SCREEN_WIDTH / 2 - scoreWidth / 2;  // Posisi X agar teks skor berada di tengah
        int scoreY = 250 + i * 28;  // Posisi Y untuk menampilkan skor, semakin turun untuk setiap skor berikutnya
        DrawText(scoreText, scoreX, scoreY, 20, WHITE);  // Gambar teks skor di layar
    }
}