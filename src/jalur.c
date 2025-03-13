#include "../include/jalur.h"
#include <raylib.h>
#include "../include/config.h"

void draw_lanes()
{
    int lane_width = SCREEN_WIDTH / MAX_LANES;
    for (int i = 1; i < MAX_LANES; i++)
    {
        int position_x = i * lane_width;
        for (int y = 0; y < SCREEN_HEIGHT; y += 40)
        {
            DrawLine(position_x, y, position_x, y + 20, WHITE);
        }
    }
}