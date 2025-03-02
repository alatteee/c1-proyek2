#include <SDL3/SDL.h>
#include "include/mobil.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/config.h" // Include config.h

#define NUM_CARS 1  // Jumlah mobil
#define MOVE_STEP 1  // Langkah pergerakan untuk berpindah antar jalur

// Tentukan posisi X untuk masing-masing jalur
#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

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
        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f - (i * 100), PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
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

        // Jika tombol kiri ditekan, pindahkan mobil ke jalur kiri
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            for (i = 0; i < NUM_CARS; i++) {
                // Pindahkan mobil ke jalur kiri jika mobil belum ada di jalur kiri
                if (cars[i].x > LEFT_LANE_X) {
                    cars[i].x = LEFT_LANE_X;
                    cars[i].rect.x = cars[i].x;  // Perbarui posisi rect
                }
            }
        }

        // Jika tombol kanan ditekan, pindahkan mobil ke jalur kanan
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            for (i = 0; i < NUM_CARS; i++) {
                // Pindahkan mobil ke jalur kanan jika mobil belum ada di jalur kanan
                if (cars[i].x < RIGHT_LANE_X) {
                    cars[i].x = RIGHT_LANE_X;
                    cars[i].rect.x = cars[i].x;  // Perbarui posisi rect
                }
            }
        }

        // Jika mobil berada di jalur kiri atau kanan, tombol kanan atau kiri akan memindahkannya ke tengah
        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            for (i = 0; i < NUM_CARS; i++) {
                // Pindahkan mobil ke jalur tengah jika mobil belum ada di jalur tengah
                if (cars[i].x != MIDDLE_LANE_X) {
                    cars[i].x = MIDDLE_LANE_X;
                    cars[i].rect.x = cars[i].x;  // Perbarui posisi rect
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
