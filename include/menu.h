#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Menu configuration constants
#define MENU_ITEM_SPACING 40
#define MENU_START_Y_POS (SCREEN_HEIGHT/2)

// Function prototypes
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected);
int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])());

#endif