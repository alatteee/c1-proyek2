#ifndef SKOR_H
#define SKOR_H

#include <SDL3/SDL.h>

// Struktur untuk menyimpan skor
typedef struct {
    int nilai;
} Skor;

// Fungsi untuk mengelola skor
void initSkor(Skor *skor);
void tambahSkor(Skor *skor, int poin);
void kurangiSkor(Skor *skor, int poin);
int getSkor(Skor *skor);
void tampilkanSkor(SDL_Renderer *renderer, Skor *skor);

#endif