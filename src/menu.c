#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Menu items
static const char *menuItems[MENU_ITEM_COUNT] = {
    "Start Game",
    "Options",
    "Exit"};

// Menu action function prototypes
static int startGame(void);
static int showOptions(void);
static int exitGame(void);

// Menu action function pointers
static int (*menuActions[MENU_ITEM_COUNT])(void) = {
    startGame,
    showOptions,
    exitGame};

void renderMenu(SDL_Renderer *renderer, TTF_Font *font, int selected)
{
    // Color definitions
    const SDL_Color white = {255, 255, 255, 255};
    const SDL_Color red = {255, 0, 0, 255};

    // Render title
    SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "Brick Racer", strlen("Brick Racer"), white);
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
    for (int i = 0; i < MENU_ITEM_COUNT; i++)
    {
        const SDL_Color color = (i == selected) ? red : white;

        // Perbaikan: Tambahkan strlen(menuItems[i])
        SDL_Surface *itemSurface = TTF_RenderText_Solid(font, menuItems[i], strlen(menuItems[i]), color);
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

int handleMenuInput(SDL_Event *event, int *selected)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        switch (event->key.scancode)
        {
        case SDL_SCANCODE_DOWN:
            *selected = (*selected + 1) % MENU_ITEM_COUNT;
            return 0;

        case SDL_SCANCODE_UP:
            *selected = (*selected - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
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

// Menu action implementations
static int startGame(void)
{
    printf("Starting game...\n");
    return 1;
}

static int showOptions(void)
{
    printf("Showing options...\n");
    return 2;
}

static int exitGame(void)
{
    printf("Exiting game...\n");
    return -1;
}
