/* ----------------------------------------------------------------------------- */
/* File        : lives.c                                                         */
/* ----------------------------------------------------------------------------- */

#include "../include/lives.h"  // File header untuk sistem nyawa
#include <stddef.h>            // Library untuk definisi NULL

// Fungsi untuk menggambar hati
void DrawHeart(Vector2 position, float size, Color color) {
    // Titik-titik untuk membentuk hati (dengan polygon)
    Vector2 center = {position.x + size / 2, position.y + size / 2}; // Pusat hati
    float halfSize = size / 2; // Setengah ukuran hati

    // Menggunakan 2 lingkaran dan 1 segitiga untuk membentuk hati
    DrawCircle(center.x - halfSize / 2, center.y - halfSize / 4, halfSize / 2, color); // Lingkaran kiri
    DrawCircle(center.x + halfSize / 2, center.y - halfSize / 4, halfSize / 2, color); // Lingkaran kanan

    // Segitiga bagian bawah hati
    Vector2 p1 = {center.x - halfSize, center.y - halfSize / 4}; // Titik kiri bawah
    Vector2 p2 = {center.x + halfSize, center.y - halfSize / 4}; // Titik kanan bawah
    Vector2 p3 = {center.x, center.y + halfSize * 0.8f};         // Titik atas
    DrawTriangle(p1, p2, p3, color); // Gambar segitiga
}

// Fungsi untuk menginisialisasi sistem nyawa
LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath) {
    LivesSystem livesSystem;
    livesSystem.currentLives = MAX_LIVES; // Set jumlah nyawa awal ke maksimum
    livesSystem.position = position;     // Set posisi awal untuk menggambar nyawa
    livesSystem.spacing = spacing;       // Set jarak antara setiap nyawa
    livesSystem.size = size;             // Set ukuran nyawa
    livesSystem.useTexture = (texturePath != NULL); // Gunakan tekstur jika path tidak NULL

    // Jika menggunakan tekstur, muat tekstur dari path yang diberikan
    if (livesSystem.useTexture) {
        livesSystem.heartTexture = LoadTexture(texturePath);
    }

    return livesSystem; // Kembalikan objek LivesSystem yang telah diinisialisasi
}

// Fungsi untuk menggambar nyawa di layar
void DrawLives(LivesSystem livesSystem) {
    for (int i = 0; i < MAX_LIVES; i++) {
        // Jika nyawa masih tersedia, gambar hati
        if (i < livesSystem.currentLives) {
            Vector2 heartPos = {
                livesSystem.position.x + i * livesSystem.spacing, // Hitung posisi X hati
                livesSystem.position.y                           // Posisi Y tetap
            };

            // Jika menggunakan tekstur, gambar tekstur hati
            if (livesSystem.useTexture) {
                DrawTexture(livesSystem.heartTexture, heartPos.x, heartPos.y, WHITE);
            }
            // Jika tidak, gambar hati menggunakan fungsi DrawHeart
            else {
                DrawHeart(heartPos, livesSystem.size, RED); // Gambar hati dengan warna merah
            }
        }
    }
}

// Fungsi untuk mengurangi nyawa pemain
bool ReduceLife(LivesSystem* livesSystem) {
    livesSystem->currentLives--; // Kurangi jumlah nyawa
    return livesSystem->currentLives <= 0; // Kembalikan true jika nyawa habis
}

// Fungsi untuk mereset nyawa ke nilai maksimum
void ResetLives(LivesSystem* livesSystem) {
    livesSystem->currentLives = MAX_LIVES; // Set nyawa ke nilai maksimum
}

// Fungsi untuk membersihkan sumber daya sistem nyawa
void UnloadLivesSystem(LivesSystem* livesSystem) {
    // Jika menggunakan tekstur, unload tekstur
    if (livesSystem->useTexture) {
        UnloadTexture(livesSystem->heartTexture);
    }
}