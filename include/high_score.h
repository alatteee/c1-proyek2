#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "single_linked_list.h"

#define MAX_NAME_LENGTH 20
#define MAX_HIGH_SCORES 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} HighScoreData;

// Fungsi utama
void SaveHighScore(const char *name, int score);
void DrawHighScores(Texture2D brickTexture);

// Helper functions untuk single linked list
HighScoreData* createHighScoreData(const char *name, int score);
void freeHighScoreData(void* data);
int compareHighScore(const void *a, const void *b);
void printHighScore(void* data);

#endif