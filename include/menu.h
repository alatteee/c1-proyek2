#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <SDL_ttf.h>

void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected);
int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])());

#endif