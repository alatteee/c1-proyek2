#include <raylib.h>
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);

    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    GameState gameState = STATE_MENU; // Already defined in config.h
    int selectedOption = 0;

    Car cars[NUM_CARS];
    Skor skor;
    int lives = 3;
    
    bool quit = false;

    while (!quit)
    {
        // Ensure gameState is within valid values (menu, game, game over, exit)
        if (gameState < STATE_MENU || gameState > STATE_EXIT) {
            gameState = STATE_MENU; // Reset to a valid state if it goes out of range
        }

        switch (gameState)
        {
            case STATE_MENU:
                handleMenuInput(&selectedOption, &gameState, cars, &lives, &skor);
                break;

            case STATE_GAME:
                handleCarInput(cars);
                updateRintangan();
                drawRintangan();

                // Cek tabrakan untuk setiap mobil
                for (int i = 0; i < NUM_CARS; i++) {
                    if (checkCollision(cars[i].x, cars[i].y, cars[i].width, cars[i].height)) {
                        lives--; // Kurangi nyawa jika terjadi tabrakan
                        if (lives <= 0) {
                            gameState = STATE_GAME_OVER; // Pindah ke state GAME_OVER jika nyawa habis
                        }
                    }
                }
                break;

            case STATE_GAME_OVER:
                if (IsKeyPressed(KEY_ENTER)) gameState = STATE_MENU;
                break;

            case STATE_EXIT:
                quit = true; // Keluar dari loop utama
                break;

            default:
                // Handle unexpected states, this is just for safety
                gameState = STATE_MENU; // Optionally reset to a known state
                break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState)
        {
            case STATE_MENU:
                DrawMenu(selectedOption, brickTexture); // Defined in menu.c
                break;

            case STATE_GAME:
                ClearBackground(DARKGRAY);
                draw_lanes(); // Draw lanes
                for (int i = 0; i < NUM_CARS; i++)
                {
                    renderCar(&cars[i]);
                }
                tampilkanSkor(&skor); // Show score
                break;

            case STATE_GAME_OVER:
                ClearBackground(BLACK); // Ubah ke BLACK
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
                DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
                break;
            default:
                // Handle any unexpected cases, resetting or showing a message can be done here
                break;
        }

        EndDrawing();
    }

    UnloadTexture(brickTexture);
    CloseWindow();
    return 0;
}
