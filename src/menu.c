#include "menu.h"
#include <stdio.h>

// Screen dimensions (should match your project's resolution)
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Menu items configuration
static const char *menuItems[] = {
    "Start Game",
    "Options",
    "Exit"};
static const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

// Menu action functions
static int startGame(void)
{
  printf("Starting game...\n");
  return 1; // Return 1 to indicate game should start
}

static int showOptions(void)
{
  printf("Showing options...\n");
  return 0;
}

static int exitGame(void)
{
  printf("Exiting game...\n");
  return -1; // Return -1 to indicate exit
}

// Array of menu action function pointers
static int (*menuActions[])(void) = {startGame, showOptions, exitGame};

// ======================
// Menu Rendering Function
// ======================
void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected)
{
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color red = {255, 0, 0, 255};

  // Render title
  SDL_Surface *titleSurface = ITF_RenderText_Solid(font, "Brick Racer", white);
  SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

  SDL_FRect titleRect = {
      .x = (SCREEN_WIDTH - titleSurface->w) / 2.0f,
      .y = SCREEN_HEIGHT / 4.0f,
      .w = (float)titleSurface->w,
      .h = (float)titleSurface->h};

  SDL_RenderTexture(renderer, titleTexture, NULL, &titleRect);
  SDL_DestroySurface(titleSurface);
  SDL_DestroyTexture(titleTexture);

  // Render menu items
  for (int i = 0; i < menuItemCount; i++)
  {
    SDL_Color color = (i == selected) ? red : white;

    SDL_Surface *itemSurface = ITF_RenderText_Solid(font, menuItems[i], color);
    SDL_Texture *itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurface);

    SDL_FRect itemRect = {
        .x = (SCREEN_WIDTH - itemSurface->w) / 2.0f,
        .y = MENU_START_Y_POS + (i * MENU_ITEM_SPACING),
        .w = (float)itemSurface->w,
        .h = (float)itemSurface->h};

    SDL_RenderTexture(renderer, itemTexture, NULL, &itemRect);
    SDL_DestroySurface(itemSurface);
    SDL_DestroyTexture(itemTexture);
  }
}

// ========================
// Input Handling Function
// ========================
int handleMenuInput(SDL_Event *event, int *selected, int menuCount, int (*menuActions[])())
{
  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    switch (event->key.scancode)
    {
    case SDL_SCANCODE_DOWN:
      *selected = (*selected + 1) % menuCount;
      break;

    case SDL_SCANCODE_UP:
      *selected = (*selected - 1 + menuCount) % menuCount;
      break;

    case SDL_SCANCODE_RETURN:
    case SDL_SCANCODE_SPACE:
      return menuActions[*selected]();

    default:
      break;
    }
  }
  return 0; // No action taken
}