#ifndef LANES_H
#define LANES_H

#include <SDL3/SDL.h>
#include "config.h"

#define NUM_LANES 3  // Number of lanes
#define LANE_WIDTH (SCREEN_WIDTH / NUM_LANES)  // Calculate lane width dynamically

void draw_lanes(SDL_Renderer *renderer);

#endif // LANES_H