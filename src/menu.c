#include "menu.h"
#include <stdio.h>
#include <string.h>

// Menu items and actions
static const char *menuItems[] = {
    "Start Game",
    "Options",
    "Exit"};
static const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

// Menu action implementations
static int startGame(void) { return 1; }
static int showOptions(void) { return 2; }
static int exitGame(void) { return -1; }

static int (*menuActions[])(void) = {
    startGame,
    showOptions,
    exitGame};

void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected)
{
  // Color definitions
  const SDL_Color white = {255, 255, 255, 255};
  const SDL_Color red = {255, 0, 0, 255};

  // Render title
  SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "C1 Brick Racer", white);
  SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

  SDL_FRect titleRect = {
      .x = (SCREEN_WIDTH - titleSurface->w) / 2.0f,
      .y = TITLE_Y_POS,
      .w = (float)titleSurface->w,
      .h = (float)titleSurface->h};

  SDL_RenderTexture(renderer, titleTexture, NULL, &titleRect);
  SDL_DestroySurface(titleSurface);
  SDL_DestroyTexture(titleTexture);

  // Render menu items
  for (int i = 0; i < menuItemCount; i++)
  {
    const SDL_Color color = (i == selected) ? red : white;
    const char *text = menuItems[i];

    SDL_Surface *itemSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurface);

    SDL_FRect itemRect = {
        .x = (SCREEN_WIDTH - itemSurface->w) / 2.0f,
        .y = SCREEN_HEIGHT / 2.0f + (i * MENU_ITEM_SPACING),
        .w = (float)itemSurface->w,
        .h = (float)itemSurface->h};

    SDL_RenderTexture(renderer, itemTexture, NULL, &itemRect);
    SDL_DestroySurface(itemSurface);
    SDL_DestroyTexture(itemTexture);
  }
}

int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])(void))
{
  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    switch (event->key.scancode)
    {
    case SDL_SCANCODE_DOWN:
      *selected = (*selected + 1) % menuCount;
      return 0;

    case SDL_SCANCODE_UP:
      *selected = (*selected - 1 + menuCount) % menuCount;
      return 0;

    case SDL_SCANCODE_RETURN:
    case SDL_SCANCODE_SPACE:
      return menuActions[*selected]();

    default:
      break;
    }
  }
  return 0;
}