#include "../include/lives.h"
#include <stddef.h>

// Fungsi untuk menggambar hati
void DrawHeart(Vector2 position, float size, Color color) {
    // Titik-titik untuk membentuk hati (dengan polygon)
    Vector2 center = {position.x + size/2, position.y + size/2};
    float halfSize = size/2;

    // Menggunakan 2 lingkaran dan 1 segitiga untuk membentuk hati
    DrawCircle(center.x - halfSize/2, center.y - halfSize/4, halfSize/2, color);
    DrawCircle(center.x + halfSize/2, center.y - halfSize/4, halfSize/2, color);

    // Segitiga bagian bawah hati
    Vector2 p1 = {center.x - halfSize, center.y - halfSize/4};
    Vector2 p2 = {center.x + halfSize, center.y - halfSize/4};
    Vector2 p3 = {center.x, center.y + halfSize*0.8f};
    DrawTriangle(p1, p2, p3, color);
}

// Inisialisasi LivesSystem
LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath) {
    LivesSystem livesSystem;
    livesSystem.currentLives = MAX_LIVES;
    livesSystem.position = position;
    livesSystem.spacing = spacing;
    livesSystem.size = size;
    livesSystem.useTexture = (texturePath != NULL);
    if (livesSystem.useTexture) {
        livesSystem.heartTexture = LoadTexture(texturePath);
    }
    return livesSystem;
}

// Menggambar nyawa
void DrawLives(LivesSystem livesSystem) {
    for (int i = 0; i < MAX_LIVES; i++) {
        if (i < livesSystem.currentLives) {
            Vector2 heartPos = {
                livesSystem.position.x + i * livesSystem.spacing,
                livesSystem.position.y
            };

            if (livesSystem.useTexture) {
                DrawTexture(livesSystem.heartTexture, heartPos.x, heartPos.y, WHITE);
            } else {
                DrawHeart(heartPos, livesSystem.size, RED); // Panggil DrawHeart
            }
        }
    }
}

// Mengurangi nyawa
bool ReduceLife(LivesSystem* livesSystem) {
    livesSystem->currentLives--;
    return livesSystem->currentLives <= 0;
}

// Mereset nyawa
void ResetLives(LivesSystem* livesSystem) {
    livesSystem->currentLives = MAX_LIVES;
}

// Unload resources
void UnloadLivesSystem(LivesSystem* livesSystem) {
    if (livesSystem->useTexture) {
        UnloadTexture(livesSystem->heartTexture);
    }
}