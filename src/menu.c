#include "../include/menu.h"
#include <stdio.h>
#include <raylib.h>

void showMenu()
{
    // Clear the background with black color
    ClearBackground(BLACK);

    // Set the menu item rectangle properties
    Rectangle menuItems[4] = {
        {100.0f, 100.0f, 200.0f, 50.0f}, // Start Game
        {100.0f, 160.0f, 200.0f, 50.0f}, // Options
        {100.0f, 220.0f, 200.0f, 50.0f}, // Level
        {100.0f, 280.0f, 200.0f, 50.0f}  // Exit
    };

    const char *menuTexts[4] = {"Start Game", "Options", "Level", "Exit"};

    // Load the font
    Font font = LoadFont("resources/fonts/game_over.ttf");  // Update this path as needed

    if (font.baseSize == 0)
    {
        printf("Failed to load font\n");
        return;
    }

    Color textColor = BLACK;

    // Draw the menu items (rectangles and texts)
    for (int i = 0; i < 4; i++)
    {
        // Draw the menu item rectangles
        DrawRectangleRec(menuItems[i], WHITE);

        // Draw the text inside the rectangles
        Vector2 textSize = MeasureTextEx(font, menuTexts[i], font.baseSize, 1);
        Vector2 textPosition = {
            menuItems[i].x + (menuItems[i].width - textSize.x) / 2,
            menuItems[i].y + (menuItems[i].height - textSize.y) / 2
        };
        DrawTextEx(font, menuTexts[i], textPosition, font.baseSize, 1, textColor);
    }

    // Unload the font to free memory
    UnloadFont(font);
}
