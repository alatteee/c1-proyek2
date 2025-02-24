#include "../include/jalur.h"
#include <SDL3/SDL.h>

// Fungsi untuk menggambar jalur
void drawLanes(SDL_Renderer* renderer, int screenWidth) {
    int laneWidth = screenWidth / 3;  // Membagi layar menjadi 3 kolom
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Warna putih

    int i;
    for (i = 1; i < 3; i++) {
        // Mengganti SDL_RenderDrawLine dengan SDL_RenderDrawLineF untuk kompatibilitas dengan SDL3
        SDL_RenderDrawLinesF(renderer, i * laneWidth, 0, i * laneWidth, 600);  // Menggambar garis vertikal
    }

    SDL_RenderPresent(renderer);
}
