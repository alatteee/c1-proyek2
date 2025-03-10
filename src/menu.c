#include "menu.h"
#include <stdio.h>

void showMenu(SDL_Renderer *renderer)
{
    if (!renderer)
    {
        printf("Renderer tidak valid\n");
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_FRect menuItems[4] = {
        {100.0f, 100.0f, 200.0f, 50.0f}, // Start Game
        {100.0f, 160.0f, 200.0f, 50.0f}, // Options
        {100.0f, 220.0f, 200.0f, 50.0f}, // Level
        {100.0f, 280.0f, 200.0f, 50.0f}  // Exit
    };

    for (int i = 0; i < 4; i++)
    {
        if (!SDL_RenderFillRect(renderer, &menuItems[i]))
        {
            printf("Gagal menggambar kotak menu: %s\n", SDL_GetError());
        }
    }

    SDL_RenderPresent(renderer);
}
