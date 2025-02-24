#include <SDL3/SDL.h>
#include "include/mobil.h"
#include "include/jalur.h"
#include "include/config.h" // Include config.h

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Racing Game",
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0); // Flags: 0 for default

    if (window == NULL) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Car playerCar;
    initCar(&playerCar, (SCREEN_WIDTH - PLAYER_CAR_WIDTH) / 2, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = (const Uint8*)SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            moveLeft(&playerCar);
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            moveRight(&playerCar, SCREEN_WIDTH);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Warna hitam
        SDL_RenderClear(renderer);

        // Gambar jalur
        drawLanes(renderer, SCREEN_WIDTH);

        // Gambar mobil pemain
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Warna hijau
        SDL_FRect playerCarRectF;
        SDL_RectToFRect(&playerCar.rect, &playerCarRectF);
        SDL_RenderFillRect(renderer, &playerCarRectF);

        // Update layar
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Delay untuk mencapai 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

