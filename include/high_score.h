#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>

// Mendefinisikan panjang maksimal untuk nama pemain (20 karakter)
#define MAX_NAME_LENGTH 20
// Mendefinisikan jumlah skor tertinggi yang dapat disimpan (10 skor)
#define MAX_HIGH_SCORES 10

// Struktur untuk menyimpan data skor tertinggi
typedef struct
{
    char name[MAX_NAME_LENGTH]; // Nama pemain yang mencetak skor
    int score;                  // Nilai skor yang dicapai pemain
} HighScore;

// Fungsi untuk menyimpan skor tinggi ke dalam file atau sistem penyimpanan
void SaveHighScore(const char *name, int score);
// Fungsi untuk memuat daftar skor tinggi dari file atau sistem penyimpanan
void LoadHighScores(HighScore highScores[]);
// Fungsi untuk menggambar tampilan skor tinggi pada layar dengan menggunakan tekstur
void DrawHighScores(Texture2D brickTexture);

#endif