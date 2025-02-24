#include "../include/jalur.h"
#include <SDL3/SDL.h>
#include "../include/config.h"

// Fungsi untuk menggambar jalur
void drawLanes(SDL_Renderer* renderer, int screenWidth) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
    
    // Left lane
    SDL_RenderLine(renderer, screenWidth/3, 0, screenWidth/3, SCREEN_HEIGHT);
    
    // Right lane
    SDL_RenderLine(renderer, (2*screenWidth)/3, 0, (2*screenWidth)/3, SCREEN_HEIGHT);
}
