#ifndef LIVES_H
#define LIVES_H

#include <raylib.h>

#define MAX_LIVES 3

typedef struct {
    int currentLives;
    Vector2 position;
    float spacing;
    float size;
    bool useTexture;
    Texture2D heartTexture;
} LivesSystem;

// Operasi-operasi pada LivesSystem
LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath);
void DrawLives(LivesSystem livesSystem);
bool ReduceLife(LivesSystem* livesSystem);
void ResetLives(LivesSystem* livesSystem);
void UnloadLivesSystem(LivesSystem* livesSystem);

// Deklarasi fungsi DrawHeart
void DrawHeart(Vector2 position, float size, Color color);

#endif // LIVES_H