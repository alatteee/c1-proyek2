#ifndef LIVES_H
#define LIVES_H

#include <raylib.h>

#define MAX_LIVES 3
#define INVULNERABILITY_DURATION 2.0f // Durasi invulnerability

typedef struct {
    int currentLives;
    Texture2D heartTexture;
    Vector2 position;
    float spacing;
    float size;
    bool useTexture;
} LivesSystem;

LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath);
void UnloadLivesSystem(LivesSystem* livesSystem);
void DrawLives(LivesSystem livesSystem);
bool ReduceLife(LivesSystem* livesSystem); // Kurangi nyawa dan cek game over
void ResetLives(LivesSystem* livesSystem); // Reset nyawa
void DrawHeart(Vector2 position, float size, Color color); // Deklarasi DrawHeart

#endif // LIVES_H