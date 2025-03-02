#include <SDL3/SDL.h>
#include "include/mobil.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/config.h" // Include config.h

#define NUM_CARS 1  // Jumlah mobil
#define MOVE_STEP 50  // Langkah pergerakan yang lebih besar (retro)

int main() {
    // Inisialisasi SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Membuat window
    SDL_Window* window = SDL_CreateWindow("Racing Game",
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);  // Flags: 0 for default

    if (window == NULL) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Membuat renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Array untuk menyimpan banyak mobil
    Car cars[NUM_CARS];  

    // Inisialisasi mobil
    int i;
    for (i = 0; i < NUM_CARS; i++) {
        initCar(&cars[i], (SCREEN_WIDTH - PLAYER_CAR_WIDTH) / 2.0f, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f - (i * 100), PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    }

    bool quit = false;
    SDL_Event e;

    // Loop utama permainan
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = (const Uint8*)SDL_GetKeyboardState(NULL);

        // Jika tombol kiri ditekan
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].x > 0) {
                    cars[i].x -= MOVE_STEP;  // Bergerak ke kiri dengan langkah tetap
                    cars[i].rect.x = cars[i].x;  // Pastikan rect.x juga diperbarui
                }
            }
        }

        // Jika tombol kanan ditekan
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].x + cars[i].width < SCREEN_WIDTH) {
                    cars[i].x += MOVE_STEP;  // Bergerak ke kanan dengan langkah tetap
                    cars[i].rect.x = cars[i].x;  // Pastikan rect.x juga diperbarui
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Warna hitam
        SDL_RenderClear(renderer);

        // Gambar jalur
        draw_lanes(renderer);

        // Gambar semua mobil
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Merah untuk mobil
        for (i = 0; i < NUM_CARS; i++) {
            renderCar(renderer, &cars[i]);  // Gambar mobil dengan SDL_FRect
        }

        // Update layar
        SDL_RenderPresent(renderer);

        // Delay untuk mencapai 60 FPS
        SDL_Delay(16);  
    }

    // Bersihkan dan tutup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
