#include "../include/menu.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Array untuk menyimpan teks menu
char *menuOptions[] = {"Start", "Options", "Exit"};
int menuCount = 3; // Jumlah menu

// Deklarasi fungsi menu (contoh)
int startGame(void) { return 0; }
int showOptions(void) { return 0; }
int exitGame(void) { return 0; }

// Array of function pointers untuk aksi menu
int (*menuActions[])(void) = { startGame, showOptions, exitGame };

// Fungsi untuk menampilkan menu
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected)
{
  SDL_Color white = {255, 255, 255, 255};
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect destRect;

  // Menampilkan judul game
  surface = ITF_RenderText_Solid(font, "C1 Brick Racer", white);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  destRect.x = (SCREEN_WIDTH - surface->w) / 2;
  destRect.y = SCREEN_HEIGHT / 4;
  destRect.w = surface->w;
  destRect.h = surface->h;
  SDL_RenderTexture(renderer, texture, NULL, &destRect);
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(texture);

  // Menampilkan menu pilihan
  for (int i = 0; i < menuCount; i++)
  {
    surface = ITF_RenderText_Solid(font, menuOptions[i], white);
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

    SDL_RenderTexture(renderer, texture, NULL, &destRect);
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
  }
}

// Fungsi untuk menangani input pada menu
int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])(void))
{
  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    SDL_Scancode scancode = event->key.scancode;

    switch (scancode)
    {
    case SDL_SCANCODE_DOWN:
      *selected = (*selected + 1) % menuCount;
      break;
    case SDL_SCANCODE_UP:
      *selected = (*selected - 1 + menuCount) % menuCount;
      break;
    case SDL_SCANCODE_RETURN:
      return menuActions[*selected](); // Kembalikan hasil eksekusi fungsi menu
    default:
      break; // Handle other scancodes if needed
    }
  }
  return 0; // Tidak ada aksi yang diambil
}

// Fungsi untuk membersihkan sumber daya (font)
void cleanupMenu(TTF_Font *font)
{
  if (font)
  {
    TTF_CloseFont(font);
  }
}