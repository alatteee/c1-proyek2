#include "../include/high_score.h"
#include "../include/single_linked_list.h"
#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Comparator untuk urutan descending
static int compareDesc(const void *a, const void *b) {
    const HighScoreEntry *ea = a;
    const HighScoreEntry *eb = b;
    return eb->score - ea->score;
}

// Free callback
static void freeEntry(void *data) {
    free(data);
}

// Simpan high score baru dan tulis ulang file
void SaveHighScore(const char *name, int score) {
    List *list = buatList();
    FILE *f = fopen("highscores.txt", "r");
    if (f) {
        char bufName[MAX_NAME_LENGTH];
        int  bufScore;
        while (fscanf(f, "%19s %d", bufName, &bufScore) == 2) {
            HighScoreEntry *e = malloc(sizeof *e);
            strncpy(e->name, bufName, MAX_NAME_LENGTH);
            e->score = bufScore;
            tambahDataTerurut(list, e, compareDesc);
        }
        fclose(f);
    }
    // entry baru
    HighScoreEntry *newE = malloc(sizeof *newE);
    strncpy(newE->name, name, MAX_NAME_LENGTH);
    newE->score = score;
    tambahDataTerurut(list, newE, compareDesc);

    // tulis top N kembali ke file
    f = fopen("highscores.txt", "w");
    if (f) {
        int total = ukuranList(list);
        int limit = total < MAX_HIGH_SCORES ? total : MAX_HIGH_SCORES;
        for (int i = 0; i < limit; i++) {
            HighScoreEntry *e = ambilData(list, i);
            fprintf(f, "%s %d\n", e->name, e->score);
        }
        fclose(f);
    }

    hapusList(list, freeEntry);
}

// Gambar high scores ke layar
void DrawHighScores(Texture2D brickTexture) {
    List *list = buatList();
    FILE *f = fopen("highscores.txt", "r");
    if (f) {
        char bufName[MAX_NAME_LENGTH];
        int  bufScore;
        while (fscanf(f, "%19s %d", bufName, &bufScore) == 2) {
            HighScoreEntry *e = malloc(sizeof *e);
            strncpy(e->name, bufName, MAX_NAME_LENGTH);
            e->score = bufScore;
            tambahDataTerurut(list, e, compareDesc);
        }
        fclose(f);
    }
    // gambar background dan judul
    DrawTexture(brickTexture, 0, 0, WHITE);
    const char *title = "High Scores";
    int tw = MeasureText(title, 40);
    DrawText(title, SCREEN_WIDTH/2 - tw/2, 200, 40, WHITE);

    // tampilkan daftar
    int total = ukuranList(list);
    int limit = total < MAX_HIGH_SCORES ? total : MAX_HIGH_SCORES;
    for (int i = 0; i < limit; i++) {
        HighScoreEntry *e = ambilData(list, i);
        char line[64];
        sprintf(line, "%d. %s - %d", i+1, e->name, e->score);
        int w = MeasureText(line, 20);
        DrawText(line, SCREEN_WIDTH/2 - w/2, 250 + i*28, 20, WHITE);
    }

    hapusList(list, freeEntry);
}
