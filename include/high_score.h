#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_HIGH_SCORES 10

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int score;
} HighScore;

void SaveHighScore(const char *name, int score);
void LoadHighScores(HighScore highScores[]);
void DrawHighScores(Texture2D brickTexture);

#endif