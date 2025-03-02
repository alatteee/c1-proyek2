#include "../include/jalur.h"
#include <SDL3/SDL.h>
#include "../include/config.h"

void draw_lanes(SDL_Renderer *renderer) 
{
    // Set road background color (dark gray)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    
    // Set lane divider color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int i, y;
    for (i = 1; i < NUM_LANES; i++) {
        int position_x = i * LANE_WIDTH;
        for (y = 0; y < SCREEN_HEIGHT; y += 40) {  // Dashed lane lines
            SDL_RenderDrawLine(renderer, position_x, y, position_x, y + 20);
        }
    }
}
