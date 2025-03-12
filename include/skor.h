#ifndef SKOR_H
#define SKOR_H

#include <SDL3/SDL.h>

// Struktur untuk menyimpan nilai skor
typedef struct {
    int nilai; // Nilai skor pemain
} Skor;

// Inisialisasi skor
void initSkor(Skor *skor);

// Menambah poin ke skor
void tambahSkor(Skor *skor, int poin);

// Mengurangi poin dari skor (tidak boleh negatif)
void kurangiSkor(Skor *skor, int poin);

// Mengambil nilai skor saat ini
int getSkor(const Skor *skor);

// Menampilkan skor ke dalam log SDL
void tampilkanSkor(SDL_Renderer *renderer, const Skor *skor);

#endif // SKOR_H