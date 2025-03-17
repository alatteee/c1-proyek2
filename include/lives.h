/* ----------------------------------------------------------------------------- */
/* File        : lives.h                                                         */
/* Deskripsi   : File header untuk mengelola sistem nyawa (lives) dalam game.    */
/*              Berisi definisi struktur LivesSystem dan fungsi-fungsi untuk      */
/*              menginisialisasi, menggambar, mengurangi, mereset, dan          */
/*              membersihkan sistem nyawa.                                      */
/* ----------------------------------------------------------------------------- */

#ifndef LIVES_H
#define LIVES_H

#include <raylib.h>  // Library Raylib untuk grafik dan utilitas

#define MAX_LIVES 3  // Jumlah maksimum nyawa yang dapat dimiliki pemain

// Struktur untuk merepresentasikan sistem nyawa
typedef struct {
    int currentLives;      // Jumlah nyawa saat ini
    Vector2 position;      // Posisi awal untuk menggambar nyawa (koordinat x, y)
    float spacing;         // Jarak antara setiap nyawa yang digambar
    float size;            // Ukuran nyawa (lebar dan tinggi)
    bool useTexture;       // Apakah menggunakan tekstur untuk menggambar nyawa
    Texture2D heartTexture; // Tekstur untuk menggambar nyawa (jika useTexture true)
} LivesSystem;

// Fungsi untuk menginisialisasi sistem nyawa
// Parameter:
// - position: Posisi awal untuk menggambar nyawa
// - spacing: Jarak antara setiap nyawa
// - size: Ukuran nyawa
// - texturePath: Path ke file tekstur (jika useTexture true)
// Return: Objek LivesSystem yang telah diinisialisasi
LivesSystem InitLivesSystem(Vector2 position, float spacing, float size, const char* texturePath);

// Fungsi untuk menggambar nyawa di layar
// Parameter:
// - livesSystem: Objek LivesSystem yang akan digambar
void DrawLives(LivesSystem livesSystem);

// Fungsi untuk mengurangi nyawa pemain
// Parameter:
// - livesSystem: Pointer ke objek LivesSystem
// Return: true jika nyawa berkurang, false jika nyawa sudah habis
bool ReduceLife(LivesSystem* livesSystem);

// Fungsi untuk mereset nyawa ke nilai maksimum
// Parameter:
// - livesSystem: Pointer ke objek LivesSystem
void ResetLives(LivesSystem* livesSystem);

// Fungsi untuk membersihkan sumber daya sistem nyawa (misalnya, unload tekstur)
// Parameter:
// - livesSystem: Pointer ke objek LivesSystem
void UnloadLivesSystem(LivesSystem* livesSystem);

// Fungsi untuk menggambar sebuah hati (nyawa) di layar
// Parameter:
// - position: Posisi untuk menggambar hati
// - size: Ukuran hati
// - color: Warna hati
void DrawHeart(Vector2 position, float size, Color color);

#endif // LIVES_H