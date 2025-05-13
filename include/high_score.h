#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "single_linked_list.h"
#include <raylib.h>

#define MAX_NAME_LENGTH   20
#define MAX_HIGH_SCORES   10

// Tipe data untuk satu entri high score
typedef struct {
    char name[MAX_NAME_LENGTH];
    int  score;
} HighScoreEntry;

// Tambah dan simpan satu entri baru
void SaveHighScore(const char *name, int score);

// Gambar daftar high score ke layar
void DrawHighScores(Texture2D brickTexture);

// Kalau butuh akses List langsung
List *LoadHighScoreList(void);
void  FreeHighScoreList(List *lst);

#endif // HIGH_SCORE_H
