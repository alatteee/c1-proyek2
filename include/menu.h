#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>

// Deklarasi fungsi untuk inisialisasi dan menampilkan menu
void initMenu(TTF_Font *font);
void renderMenu(SDL_Renderer *renderer, int selected);
int handleMenuInput(SDL_Event *event, int *selected);
void cleanupMenu();

#endif // MENU_H
