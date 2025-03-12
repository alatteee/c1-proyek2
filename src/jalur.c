#include "../include/jalur.h"
#include <raylib.h>
#include "../include/config.h"

void draw_lanes()
{
    int i, y;
    // Set road background color (dark gray)
    ClearBackground(DARKGRAY);

    // Set lane divider color (white)
    int num_lanes = 3;
    int lane_width = SCREEN_WIDTH / num_lanes;

    for (i = 1; i < num_lanes; i++)
    {
        int position_x = i * lane_width;
        for (y = 0; y < SCREEN_HEIGHT; y += 40)
        { // Dashed lane lines
            DrawLine(position_x, y, position_x, y + 20, WHITE);
        }
    }
}
