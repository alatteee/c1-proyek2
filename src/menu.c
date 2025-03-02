#include "menu.h"
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Array untuk menyimpan teks menu
char *menuOptions[] = {"Start", "Options", "Exit"};
int menuCount = 3; // Jumlah menu

// Array of Integer untuk menyimpan nilai pilihan menu (0 - Start, 1 - Options, 2 - Exit)
int menuActions[] = {0, 1, 2}; // Menandakan aksi yang dipilih berdasarkan indeks

// Deklarasi variabel global untuk font
TTF_Font *font = NULL;

// Fungsi untuk inisialisasi menu
void initMenu(TTF_Font *newFont)
{
    font = newFont;
}

// Fungsi untuk menampilkan menu
void renderMenu(SDL_Renderer *renderer, int selected)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect destRect;

    // Menampilkan judul game
    surface = TTF_RenderText_Solid(font, "C1 Brick Racer", white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    destRect.x = (SCREEN_WIDTH - surface->w) / 2;
    destRect.y = SCREEN_HEIGHT / 4;
    destRect.w = surface->w;
    destRect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Menampilkan menu pilihan
    for (int i = 0; i < menuCount; i++)
    {
        surface = TTF_RenderText_Solid(font, menuOptions[i], white);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        destRect.x = (SCREEN_WIDTH - surface->w) / 2;
        destRect.y = SCREEN_HEIGHT / 2 + i * 40;
        destRect.w = surface->w;
        destRect.h = surface->h;

        // Menandakan pilihan yang sedang dipilih
        if (i == selected)
        {
            SDL_SetTextureColorMod(texture, 255, 0, 0); // Warna merah untuk pilihan yang dipilih
        }

        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

// Fungsi untuk menangani input pada menu
void handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])())
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->keyboard.keysym == SDLK_DOWN)
        {
            *selected = (*selected + 1) % menuCount; // Navigasi ke bawah
        }
        if (event->keyboard.keysym == SDLK_UP)
        {
            *selected = (*selected - 1 + menuCount) % menuCount; // Navigasi ke atas
        }
        if (event->keyboard.keysym == SDLK_RETURN)
        {
            menuActions[*selected](); // Eksekusi aksi berdasarkan pilihan
        }
    }
    return -1; // Tidak ada aksi
}

// Fungsi untuk membersihkan sumber daya (font)
void cleanupMenu()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
}
