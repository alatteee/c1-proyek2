#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Configuration
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MENU_ITEM_SPACING 60
#define TITLE_Y_POS (SCREEN_HEIGHT * 0.25f)

// Menu functions
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected);
int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])(void));

#endif