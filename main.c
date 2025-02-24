#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h> // Untuk exit

// Konstanta untuk ukuran jendela dan warna
#define SCREEN_WIDTH     640
#define SCREEN_HEIGHT    480
#define TRACK_COLOR_ROAD 0x555555FF // Abu-abu gelap untuk jalan
#define TRACK_COLOR_BORDER 0x33AA33FF // Hijau terang untuk batas lintasan
#define CAR_COLOR        0xFF0000FF // Merah untuk mobil

int main(int argc, char* argv[]) {
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Membuat jendela
    SDL_Window* window = SDL_CreateWindow("SDL3 Racing Track C", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Membuat renderer untuk menggambar
    // Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC; // SDL3 tidak lagi menggunakan flags ini seperti ini
    // Ubah parameter kedua dari NULL menjadi 0 untuk kompatibilitas SDL3 - sekarang hanya 0 untuk default atau nama sebagai string
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int windowWidth, windowHeight;
    SDL_GetCurrentRenderOutputSize(renderer, &windowWidth, &windowHeight); // Gunakan SDL_GetCurrentRenderOutputSize di SDL3

    int running = 1;
    SDL_Event event;

    // Posisi awal mobil
    SDL_FRect carRect = { windowWidth / 2 - 10, windowHeight / 2 - 10, 20, 20 };
    float carSpeed = 2.0f;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
            // Contoh input sederhana: panah kiri/kanan untuk gerakkan mobil
            if (event.type == SDL_EVENT_KEY_DOWN) {
                // Gunakan event.key.key bukan event.key.keysym.sym di SDL3
                switch (event.key.key) {
                    case SDLK_LEFT:  carRect.x -= carSpeed; break;
                    case SDLK_RIGHT: carRect.x += carSpeed; break;
                    case SDLK_UP:    carRect.y -= carSpeed; break;
                    case SDLK_DOWN:  carRect.y += carSpeed; break;
                }
            }
        }

        // Set warna gambar untuk latar belakang (hitam)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer); // Bersihkan layar

        // Warna untuk jalan lintasan
        SDL_Color roadColor = { (TRACK_COLOR_ROAD >> 24) & 0xFF, (TRACK_COLOR_ROAD >> 16) & 0xFF, (TRACK_COLOR_ROAD >> 8) & 0xFF, TRACK_COLOR_ROAD & 0xFF };
        SDL_SetRenderDrawColor(renderer, roadColor.r, roadColor.g, roadColor.b, roadColor.a);

        // Menggambar jalan lintasan (persegi panjang di tengah)
        SDL_FRect roadRect = { windowWidth / 4.0f, windowHeight / 4.0f, windowWidth / 2.0f, windowHeight / 2.0f };
        SDL_RenderFillRect(renderer, &roadRect);

        // Warna untuk batas lintasan
        SDL_Color borderColor = { (TRACK_COLOR_BORDER >> 24) & 0xFF, (TRACK_COLOR_BORDER >> 16) & 0xFF, (TRACK_COLOR_BORDER >> 8) & 0xFF, TRACK_COLOR_BORDER & 0xFF };
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);

        // Menggambar batas lintasan (persegi panjang luar)
        SDL_FRect borderRect = { windowWidth / 8.0f, windowHeight / 8.0f, windowWidth * 3.0f / 4.0f, windowHeight * 3.0f / 4.0f };
        SDL_RenderFillRect(renderer, &borderRect);

        // Warna untuk mobil
        SDL_Color carColor = { (CAR_COLOR >> 24) & 0xFF, (CAR_COLOR >> 16) & 0xFF, (CAR_COLOR >> 8) & 0xFF, CAR_COLOR & 0xFF };
        SDL_SetRenderDrawColor(renderer, carColor.r, carColor.g, carColor.b, carColor.a);

        // Menggambar mobil (persegi panjang merah)
        SDL_RenderFillRect(renderer, &carRect);

        SDL_RenderPresent(renderer); // Update layar

        SDL_Delay(16); // Delay untuk frame rate (sekitar 60 FPS)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}