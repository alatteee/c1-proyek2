#include "../include/skor.h"
#include <SDL3/SDL.h>
#include <stdio.h>

void initSkor(Skor *skor) {
    skor->nilai = 0;
}

void tambahSkor(Skor *skor, int poin) {
    skor->nilai += poin;
}

void kurangiSkor(Skor *skor, int poin) {
    skor->nilai -= poin;
    if (skor->nilai < 0) {
        skor->nilai = 0;  // Pastikan skor tidak negatif
    }
}

int getSkor(Skor *skor) {
    return skor->nilai;
}

void tampilkanSkor(SDL_Renderer *renderer, Skor *skor) {
    char skorText[50];
    sprintf(skorText, "Skor: %d", skor->nilai);
    SDL_Log("%s", skorText);
}