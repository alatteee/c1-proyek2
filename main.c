#include <raylib.h>
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"

#define NUM_CARS 1 // Jumlah mobil pemain

// Koordinat jalur untuk mobil
#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

// Enum untuk state game
typedef enum
{
    STATE_MENU,
    STATE_GAME,
    STATE_GAME_OVER,
    STATE_EXIT
} GameState;

int main()
{
    // Inisialisasi Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60); // Set FPS untuk menghindari flicker

    // Load tekstur brick untuk animasi
    Texture2D brickTexture = LoadTexture("resources/coba.jpg"); // Pastikan file gambar ada di folder resources

    // Variabel state game
    GameState gameState = STATE_MENU;
    int selectedOption = 0;
    float brickOffset = 0; // Offset untuk animasi brick

    // Inisialisasi mobil, rintangan, dan skor
    Car cars[NUM_CARS];
    Skor skor;
    int lives = 3;
    bool quit = false;

    while (!quit)
    {
        // Update animasi brick
        brickOffset += 1.0f; // Geser tekstur brick ke kanan
        if (brickOffset >= brickTexture.width)
        {
            brickOffset = 0; // Reset offset jika melebihi lebar tekstur
        }

        // Handle input berdasarkan state game
        switch (gameState)
        {
        case STATE_MENU:
        {
            if (IsKeyPressed(KEY_UP))
            {
                selectedOption--;
                if (selectedOption < 0)
                    selectedOption = 2; // Sesuai jumlah opsi menu
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption++;
                if (selectedOption > 2)
                    selectedOption = 0;
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                switch (selectedOption)
                {
                case 0: // Start Game
                    for (int i = 0; i < NUM_CARS; i++)
                    {
                        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
                    }
                    initRintangan();
                    initSkor(&skor);
                    lives = 3;
                    gameState = STATE_GAME;
                    break;

                case 1: // Options
                    // Tambahkan logika untuk menu Options
                    break;

                case 2: // Exit
                    gameState = STATE_EXIT;
                    break;
                }
            }
            break;
        }

        case STATE_GAME:
        {
            if (IsKeyPressed(KEY_ESCAPE))
                gameState = STATE_MENU;

            // Gerakkan mobil berdasarkan input
            for (int i = 0; i < NUM_CARS; i++)
            {
                if (IsKeyDown(KEY_LEFT) && cars[i].x > LEFT_LANE_X)
                    cars[i].x -= cars[i].speed;
                if (IsKeyDown(KEY_RIGHT) && cars[i].x < RIGHT_LANE_X)
                    cars[i].x += cars[i].speed;
                if (IsKeyDown(KEY_UP) && cars[i].y > 0)
                    cars[i].y -= cars[i].speed;
                if (IsKeyDown(KEY_DOWN) && cars[i].y + cars[i].height < SCREEN_HEIGHT)
                    cars[i].y += cars[i].speed;
            }

            // Update rintangan dan cek tabrakan
            updateRintangan();
            for (int i = 0; i < NUM_CARS; i++)
            {
                if (checkCollision(cars[i].x, cars[i].y, cars[i].width, cars[i].height))
                {
                    lives--;
                    kurangiSkor(&skor, 10);

                    if (lives <= 0)
                        gameState = STATE_GAME_OVER;
                    else
                    {
                        // Reset posisi mobil setelah tabrakan
                        cars[i].x = MIDDLE_LANE_X;
                        cars[i].y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10;
                    }
                }
            }
            break;
        }

        case STATE_GAME_OVER:
        {
            if (IsKeyPressed(KEY_ENTER))
                gameState = STATE_MENU;
            break;
        }

        case STATE_EXIT:
            quit = true;
            break;
        }

        // Render game berdasarkan state
        BeginDrawing();
        ClearBackground(RAYWHITE); // Bersihkan layar dengan warna putih

        switch (gameState)
        {
        case STATE_MENU:
            DrawMenu(selectedOption, brickTexture); // Gambar menu dengan animasi brick
            break;

        case STATE_GAME:
            ClearBackground(DARKGRAY); // Bersihkan layar dengan warna hitam
            draw_lanes();
            drawRintangan();
            for (int i = 0; i < NUM_CARS; i++)
            {
                renderCar(&cars[i]);
            }
            tampilkanSkor(&skor);
            break;

        case STATE_GAME_OVER:
            ClearBackground(BLACK);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
            DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
            break;

        case STATE_EXIT:
            break;
        }

        EndDrawing();
    }

    // Unload texture saat program selesai
    UnloadTexture(brickTexture);
    CloseWindow();
    return 0;
}