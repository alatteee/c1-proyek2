#include "../include/high_score.h"
#include "../include/config.h"
#include <raylib.h>

void SaveHighScore(const char *name, int score)
{
    HighScore highScores[MAX_HIGH_SCORES];
    LoadHighScores(highScores);

    // Cek apakah skor baru termasuk dalam high score
    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        if (score > highScores[i].score)
        {
            // Geser skor yang ada
            for (int j = MAX_HIGH_SCORES - 1; j > i; j--)
            {
                strcpy(highScores[j].name, highScores[j - 1].name);
                highScores[j].score = highScores[j - 1].score;
            }
            // Simpan skor baru
            strcpy(highScores[i].name, name);
            highScores[i].score = score;
            break;
        }
    }

    // Simpan kembali ke file
    FILE *file = fopen("highscores.txt", "w");
    if (file)
    {
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            fprintf(file, "%s %d\n", highScores[i].name, highScores[i].score);
        }
        fclose(file);
    }
}

void LoadHighScores(HighScore highScores[])
{
    FILE *file = fopen("highscores.txt", "r");
    if (file)
    {
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            fscanf(file, "%s %d", highScores[i].name, &highScores[i].score);
        }
        fclose(file);
    }
    else
    {
        // Inisialisasi high score kosong jika file tidak ada
        for (int i = 0; i < MAX_HIGH_SCORES; i++)
        {
            strcpy(highScores[i].name, "---");
            highScores[i].score = 0;
        }
    }
}

void DrawHighScores(Texture2D brickTexture)
{
    HighScore highScores[MAX_HIGH_SCORES];
    LoadHighScores(highScores);

    // Gambar latar belakang
    DrawTexture(brickTexture, 0, 0, WHITE);

    // Gambar judul
    const char *title = "High Scores";
    int titleWidth = MeasureText(title, 40);
    int titleX = SCREEN_WIDTH / 2 - titleWidth / 2;
    int titleY = 100; // Posisi Y judul
    DrawText(title, titleX, titleY, 40, WHITE);

    // Gambar daftar high score
    for (int i = 0; i < MAX_HIGH_SCORES; i++)
    {
        char scoreText[50];
        snprintf(scoreText, sizeof(scoreText), "%d. %s - %d", i + 1, highScores[i].name, highScores[i].score);
        int scoreWidth = MeasureText(scoreText, 20);
        int scoreX = SCREEN_WIDTH / 2 - scoreWidth / 2;
        int scoreY = 250 + i * 40; // Lebih turun lagi
        DrawText(scoreText, scoreX, scoreY, 20, WHITE);
    }
}