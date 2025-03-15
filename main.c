#include <raylib.h>
#include <stddef.h>
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"
#include "include/lives.h"

int main() {


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);

    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    LivesSystem livesSystem = InitLivesSystem((Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);
    GameState gameState = STATE_MENU;
    int selectedOption = 0;

    Car cars[NUM_CARS];
    for (int i = 0; i < NUM_CARS; i++) {
        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    }

    Skor skor;
    initSkor(&skor);

    bool quit = false;

    while (!quit) {
        float deltaTime = GetFrameTime();

        switch (gameState) {
            case STATE_MENU:
                handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
                break;
        
            case STATE_GAME:
                handleCarInput(cars);
                updateRintangan(&skor);
                drawRintangan();
        
                for (int i = 0; i < NUM_CARS; i++) {
                    updateCarInvulnerability(&cars[i], deltaTime);
                
                    for (int lane = 0; lane < MAX_LANES; lane++) {
                        for (int j = 0; j < MAX_OBSTACLES; j++) {
                            // Hanya cek tabrakan jika rintangan aktif (y >= 0 dan width > 0)
                            if (rintangan[lane][j].y >= 0 && rintangan[lane][j].width > 0) {
                                Rectangle obstacle = {
                                    rintangan[lane][j].x, 
                                    rintangan[lane][j].y, 
                                    rintangan[lane][j].width, 
                                    rintangan[lane][j].height
                                };
                
                                if (checkCarCollision(&cars[i], obstacle)) {
                                    if (ReduceLife(&livesSystem)) {
                                        gameState = STATE_GAME_OVER;
                                    }
                                    resetCarPosition(&cars[i]);
                                }
                            }
                        }
                    }
                }
                break;
        
            case STATE_GAME_OVER:
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = STATE_MENU;
                    ResetLives(&livesSystem);
                    initSkor(&skor);
                }
                break;
        
            case STATE_EXIT:
                // Tambahkan penanganan untuk STATE_EXIT
                quit = true; // Keluar dari loop utama
                break;
        
            default:
                gameState = STATE_MENU; // Kembali ke menu jika state tidak valid
                break;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState) {
            case STATE_MENU:
                DrawMenu(selectedOption, brickTexture);
                break;

            case STATE_GAME:
                ClearBackground(DARKGRAY);
                draw_lanes();
                for (int i = 0; i < NUM_CARS; i++) {
                    renderCar(&cars[i]);
                }
                tampilkanSkor(&skor);
                DrawLives(livesSystem); // Pastikan ini dipanggil
                break;

            case STATE_GAME_OVER:
                ClearBackground(BLACK);
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
                DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
                break;

             default:
                // Penanganan default jika ada state yang tidak terduga
                break;
        }

        EndDrawing();
    }

    UnloadTexture(brickTexture);
    UnloadLivesSystem(&livesSystem);
    CloseWindow();
    return 0;
}