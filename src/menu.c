#include "../include/menu.h"
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>

void showMenu(SDL_Renderer *renderer)
{
    if (!renderer)
    {
        printf("Renderer tidak valid\n");
        return;
    }

    if (TTF_Init() != 0)
    {
        printf("Gagal inisialisasi SDL_ttf: %s\n", SDL_GetError());
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

    const char *menuTexts[4] = {"Start Game", "Options", "Level", "Exit"};

    TTF_Font *font = TTF_OpenFont("/fonts/game_over.ttf", 24);
    if (!font)
    {
        printf("Gagal memuat font: %s\n", SDL_GetError());
        TTF_Quit();
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    for (int i = 0; i < 4; i++)
    {
        if (!SDL_RenderFillRect(renderer, &menuItems[i]))
        {
            printf("Gagal menggambar kotak menu: %s\n", SDL_GetError());
        }
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuTexts[i], strlen(menuTexts[i]), textColor);
        if (!textSurface)
        {
            printf("Gagal membuat permukaan teks: %s\n", SDL_GetError());
            continue;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_DestroySurface(textSurface);

        if (!textTexture)
        {
            printf("Gagal membuat tekstur teks: %s\n", SDL_GetError());
            continue;
        }

        SDL_FRect textRect = {
            menuItems[i].x + (menuItems[i].w - textSurface->w) / 2,
            menuItems[i].y + (menuItems[i].h - textSurface->h) / 2,
            textSurface->w,
            textSurface->h};

        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }

    SDL_RenderPresent(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
}