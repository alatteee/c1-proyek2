#include "../include/jalur.h"
#include <SDL3/SDL.h>
#include "../include/config.h"


void draw_lanes(SDL_Renderer *renderer) {
    int i, y;
    // Set road background color (dark gray)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_FRect road = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &road);
    
    // Set lane divider color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int num_lanes = 3;
    int lane_width = SCREEN_WIDTH / num_lanes;
    for (i = 1; i < num_lanes; i++) {
        int position_x = i * lane_width;
        for (y = 0; y < SCREEN_HEIGHT; y += 40) {  // Dashed lane lines
            SDL_RenderLine(renderer, position_x, y, position_x, y + 20);
        }
    }
}