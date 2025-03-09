#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Screen dimensions
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Menu configuration
#define MENU_ITEM_COUNT 3
#define MENU_ITEM_SPACING 60
#define TITLE_Y_POS 150.0f

// Function prototypes
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected);
int handleMenuInput(SDL_Event *event, int *selected);

#endif