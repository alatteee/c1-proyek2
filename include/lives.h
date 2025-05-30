/* ----------------------------------------------------------------------------- */
/* File        : lives.h                                                         */
/* Deskripsi   : Header sistem nyawa pemain dalam game.                          */
/* ----------------------------------------------------------------------------- */

#ifndef LIVES_H
#define LIVES_H

#include <raylib.h>

#define MAX_LIVES 3  // Nyawa maksimum

// Struktur sistem nyawa
typedef struct {
    int currentLives;      
    Vector2 position;      
    float spacing;         
    float size;            
    bool useTexture;       
    Texture2D heartTexture;
} LivesSystem;

// Inisialisasi sistem nyawa
LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath);

// Gambar nyawa ke layar
void DrawLives(LivesSystem livesSystem);

// Kurangi nyawa, return false jika habis
bool ReduceLife(LivesSystem* livesSystem);

// Reset nyawa ke MAX_LIVES
void ResetLives(LivesSystem* livesSystem);

// Bersihkan resource sistem nyawa
void UnloadLivesSystem(LivesSystem* livesSystem);

// Gambar 1 hati manual
void DrawHeart(Vector2 position, float size, Color color);

#endif // LIVES_H
