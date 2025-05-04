#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_HIGH_SCORES 10

typedef struct HighScoreNode
{
    char name[MAX_NAME_LENGTH];
    int score;
    struct HighScoreNode *next;
} HighScoreNode;

// Fungsi utama
void SaveHighScore(const char *name, int score);
void LoadHighScores(HighScoreNode **head);
void DrawHighScores(Texture2D brickTexture);
void FreeHighScores(HighScoreNode *head);

#endif
