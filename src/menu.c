#include <SDL3/SDL.h>
#include <stdio.h>
#include "menu.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL gagal diinisialisasi: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("C1 Brick Racer Menu", 800, 600, SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("Gagal membuat window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // GANTI PARAMETER KEDUA DENGAN "opengl" ATAU NULL
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        printf("Gagal membuat renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    showMenu(renderer);

    SDL_Delay(3000); // Biar menu-nya nongol 3 detik

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    if (!window)
    {
        printf("Window gagal dibuat\n");
    }
    if (!renderer)
    {
        printf("Renderer gagal dibuat\n");
    }

    return 0;
}
