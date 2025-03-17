#include <raylib.h>
#include <stdio.h>
#include "include/mobil.h"
#include "include/finish_line.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"
#include "include/lives.h"
#include "include/ADT.h"
#include "src/level.c"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);

    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    LivesSystem livesSystem = InitLivesSystem((Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);
    GameState gameState = STATE_MENU;
    int selectedOption = 0;

    Car cars[NUM_CARS];
    for (int i = 0; i < NUM_CARS; i++)
    {
        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
        printf("PLAYER_CAR_WIDTH: %d, PLAYER_CAR_HEIGHT: %d\n", PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT);
    }

    Skor skor;
    initSkor(&skor);

    int selectedLevel = 0; // Level yang dipilih (default: level 0 / Easy)
    bool quit = false;
    bool collisionOccurred = false;

    float gameTimer = 0.0f;         // Timer untuk menghitung waktu permainan
    bool finishLineVisible = false; // Apakah garis finish sudah muncul?

    while (!quit)
    {
        if (WindowShouldClose())
        {
            quit = true;
        }

        float deltaTime = GetFrameTime();

        switch (gameState)
        {
            case STATE_MENU:
                handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    gameState = STATE_EXIT;
                }
                if (IsKeyPressed(KEY_ENTER) && selectedOption == 0)
                {
                    initRintangan();
                }
                break;

            case STATE_LEVEL_MENU:
                handleLevelMenuInput(&selectedLevel, &gameState);
                break;

            case STATE_GAME:
            {
                Level currentLevel = levels[selectedLevel];
                printf("Selected Level: %d, Obstacle Speed: %d, Num Obstacles: %d\n", 
                       selectedLevel, currentLevel.obstacleSpeed, currentLevel.numObstacles);
                
                gameTimer += deltaTime;
                if (gameTimer >= 10.0f && !finishLineVisible)
                {
                    finishLineVisible = true;
                }

                // Update game hanya jika belum menyelesaikan balapan
                handleCarInput(&cars[0]);
                updateRintangan(&skor, currentLevel.obstacleSpeed, false);

                // Cek finish line. Jika sudah dilewati, pindah ke STATE_WIN
                if (finishLineVisible && CheckFinishLineCollision(&cars[0]))
                {
                    gameState = STATE_WIN;
                }
                
                collisionOccurred = false;
                for (int i = 0; i < NUM_CARS && !collisionOccurred; i++)
                {
                    updateCarInvulnerability(&cars[i], deltaTime);
                    for (int lane = 0; lane < MAX_LANES && !collisionOccurred; lane++)
                    {
                        for (int j = 0; j < MAX_OBSTACLES && !collisionOccurred; j++)
                        {
                            if (rintangan[lane][j].y >= 0 && rintangan[lane][j].width > 0)
                            {
                                Rectangle obstacle = { 
                                    rintangan[lane][j].x, 
                                    rintangan[lane][j].y,
                                    rintangan[lane][j].width, 
                                    rintangan[lane][j].height 
                                };
                                if (checkCarCollision(&cars[i], obstacle))
                                {
                                    if (ReduceLife(&livesSystem))
                                    {
                                        gameState = STATE_GAME_OVER;
                                    }
                                    else
                                    {
                                        gameState = STATE_COLLISION;
                                    }
                                    collisionOccurred = true;
                                }
                            }
                        }
                    }
                }
                break;
            }

            case STATE_COLLISION:
                if (IsKeyPressed(KEY_C))
                {
                    gameState = STATE_GAME;
                }
                if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
                {
                    gameState = STATE_MENU;
                }
                break;

            case STATE_WIN:
                // Tampilkan pesan menang dan tunggu Enter untuk kembali ke menu
                if (IsKeyPressed(KEY_ENTER))
                {
                    ScoreRecord record = CreateScoreRecord(skor.nilai);
                    if (SaveScoreRecord(&record, "score.txt"))
                    {
                        printf("Score %d pada %s berhasil disimpan.\n", record.score, record.date);
                    }
                    else
                    {
                        printf("Gagal menyimpan skor.\n");
                    }
                    gameState = STATE_MENU;
                    ResetLives(&livesSystem);
                    initSkor(&skor);
                    gameTimer = 0.0f;
                    finishLineVisible = false;
                }
                break;

            case STATE_GAME_OVER:
                if (IsKeyPressed(KEY_ENTER))
                {
                    ScoreRecord record = CreateScoreRecord(skor.nilai);
                    if (SaveScoreRecord(&record, "score.txt"))
                    {
                        printf("Score %d pada %s berhasil disimpan.\n", record.score, record.date);
                    }
                    else
                    {
                        printf("Gagal menyimpan skor.\n");
                    }
                    gameState = STATE_MENU;
                    ResetLives(&livesSystem);
                    initSkor(&skor);
                    gameTimer = 0.0f;
                    finishLineVisible = false;
                }
                break;

            case STATE_EXIT:
                quit = true;
                break;

            default:
                gameState = STATE_MENU;
                break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState)
        {
            case STATE_MENU:
                DrawMenu(selectedOption, brickTexture);
                break;

            case STATE_LEVEL_MENU:
                DrawLevelMenu(selectedLevel, brickTexture);
                break;

            case STATE_GAME:
                ClearBackground(DARKGRAY);
                draw_lanes();
                if (finishLineVisible)
                {
                    DrawFinishLine();
                }
                drawRintangan(false);
                renderCar(&cars[0]);
                tampilkanSkor(&skor);
                DrawLives(livesSystem);
                break;

            case STATE_COLLISION:
                ClearBackground(DARKGRAY);
                draw_lanes();
                drawRintangan(false);
                renderCar(&cars[0]);
                tampilkanSkor(&skor);
                DrawLives(livesSystem);
                DrawText("Collision Detected!", SCREEN_WIDTH / 2 - MeasureText("Collision Detected!", 30) / 2,
                         SCREEN_HEIGHT / 2 - 50, 30, RED);
                DrawText("Press C to Continue, Q/ESC to Quit", 
                         SCREEN_WIDTH / 2 - MeasureText("Press C to Continue, Q/ESC to Quit", 20) / 2,
                         SCREEN_HEIGHT / 2, 20, WHITE);
                break;

            case STATE_WIN:
                ClearBackground(DARKGRAY);
                draw_lanes();
                DrawFinishLine();
                drawRintangan(false);
                renderCar(&cars[0]);
                tampilkanSkor(&skor);
                DrawLives(livesSystem);
                DrawText("You Win!", SCREEN_WIDTH / 2 - MeasureText("You Win!", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
                DrawText("Press ENTER to return to Menu", 
                         SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2,
                         SCREEN_HEIGHT / 2 + 50, 20, WHITE);
                break;

            case STATE_GAME_OVER:
                ClearBackground(BLACK);
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
                DrawText("Press ENTER to return to Menu", 
                         SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2,
                         SCREEN_HEIGHT / 2 + 20, 20, WHITE);
                break;

            default:
                break;
        }
        EndDrawing();
    }

    UnloadTexture(brickTexture);
    UnloadLivesSystem(&livesSystem);
    CloseWindow();
    return 0;
}