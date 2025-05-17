#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "include/mobil.h"
#include "include/finish_line.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"
#include "include/lives.h"
#include "include/high_score.h"
#include "include/mobil_selection.h"
#include "include/level.h"
#include "include/single_linked_list.h"
#include "include/double_linked_list.h"

// Musik
extern Music menuMusic; // di‐load di main.c
Music gameMusic;

int main(void) {
    // --- Inisialisasi level (single-linked) ---LevelNode
    List *levelList = CreateLevelList();
    AppendLevel(levelList, "Easy",   5);
    AppendLevel(levelList, "Medium", 8);
    AppendLevel(levelList, "Hard",   12);



    // --- Window & Audio ---
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);
    InitAudioDevice();
    menuMusic = LoadMusicStream("resources/menusound.mp3");
    gameMusic = LoadMusicStream("resources/racingcarsound.mp3");
    SetMusicVolume(menuMusic, 1.5f);
    SetMusicVolume(gameMusic, 1.5f);
    PlayMusicStream(menuMusic);

    // --- Load Background ---
    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    // --- Lives ---
    LivesSystem livesSystem = InitLivesSystem(
        (Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);

    // --- Player Car default (sementara) ---
    Car cars[NUM_CARS];
    initCar(&cars[0],
        MIDDLE_LANE_X,
        SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10,
        PLAYER_CAR_WIDTH,
        PLAYER_CAR_HEIGHT,
        10,
        "resources/mobil/biasa_kuning.png");

    // --- List pilihan mobil ---
    List *carList = createCarList();

    // --- Skor ---
    Skor skor; initSkor(&skor);

    // --- Finish line ---
    List *finishList      = InitFinishLine();
    bool  finishVisible   = false;
    float gameTimer       = 0.0f;
    bool  rInit           = false;

    // --- Nama pemain ---
    char playerName[MAX_NAME_LENGTH] = "";

    // --- Inisialisasi menu (double-linked) ---
    InitializeMenuSystem(brickTexture, levelList, carList);
    SetCurrentMenu(STATE_MENU); // Tidak perlu kirim menuSystem


    GameState gameState = STATE_MENU;
    bool      quit      = false;

    // --- Game Loop ---
    while (!quit && !WindowShouldClose()) {
        float dt = GetFrameTime();

        // update musik
        if (isMusicEnabled) {
            UpdateMusicStream(menuMusic);
            UpdateMusicStream(gameMusic);
        }

        // --- Input & State Transisi ---
        if (gameState == STATE_MENU
         || gameState == STATE_LEVEL_MENU
         || gameState == STATE_INPUT_NAME
         || gameState == STATE_SELECT_CAR
         || gameState == STATE_SETTINGS) {
            HandleMenuInput(&gameState);
            SetCurrentMenu(gameState);
        } else {
            switch (gameState) {
                case STATE_GAME:
                    if (!rInit) {
                        initRintangan();
                        rInit = true;
                    }
                    gameTimer += dt;
                    if (gameTimer >= 10.0f) finishVisible = true;

                    handleCarInput(&cars[0]);
                    Level *selectedLevel = getLevelByIndex(
                        ((LevelMenuData*)currentMenu->data)->levelList,
                        ((LevelMenuData*)currentMenu->data)->selectedLevel
                    );
                    if (selectedLevel)
                        updateRintangan(&skor, selectedLevel->obstacleSpeed);
                                        if (finishVisible && CheckFinishLineCollision(&cars[0]))
                        gameState = STATE_WIN;

                    updateCarInvulnerability(&cars[0], dt);
                    if (!cars[0].isInvulnerable
                     && checkCollision(cars[0].x,cars[0].y,
                                       cars[0].width,cars[0].height) > 0) {
                        gameState = ReduceLife(&livesSystem)
                                  ? STATE_GAME_OVER
                                  : STATE_COLLISION;
                    }
                    break;

                case STATE_COLLISION:
                    if (IsKeyPressed(KEY_C))      gameState = STATE_GAME;
                    if (IsKeyPressed(KEY_ESCAPE)) gameState = STATE_MENU;
                    break;

                case STATE_WIN:
                case STATE_GAME_OVER:
                    if (IsKeyPressed(KEY_ENTER)) {
                        // ambil nama dari InputNameData
                        InputNameData *in = (InputNameData*)(
                            // cari node INPUT_NAME di menuList
                            ((DLNode*)menuList->head->next)->data
                        );
                        strcpy(playerName, in->playerName);
                        SaveHighScore(playerName, skor.nilai);
                        gameState = STATE_HIGH_SCORES;
                    }
                    break;

                case STATE_HIGH_SCORES:
                    if (IsKeyPressed(KEY_ENTER)) {
                        gameState = STATE_MENU;
                        ResetLives(&livesSystem);
                        initSkor(&skor);
                        gameTimer = 0.0f;
                        finishVisible = false;
                        if (rInit) {
                            freeRintangan();
                            rInit = false;
                        }
                    }
                    break;

                case STATE_EXIT:
                    quit = true;
                    break;

                default: break;
            }
        }

        // --- Render ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == STATE_MENU
         || gameState == STATE_LEVEL_MENU
         || gameState == STATE_INPUT_NAME
         || gameState == STATE_SELECT_CAR
         || gameState == STATE_SETTINGS) {
            DrawMenu();
        } else {
            switch (gameState) {
                case STATE_GAME:
                    ClearBackground(DARKGRAY);
                    draw_lanes();
                    if (finishVisible) DrawFinishLine(finishList);
                    drawRintangan();
                    renderCar(&cars[0]);
                    tampilkanSkor(&skor);
                    DrawLives(livesSystem);
                    DrawText("Press F1 for debug view",
                             10, SCREEN_HEIGHT-20, 10, GRAY);
                    break;
                case STATE_COLLISION:   /* … */ break;
                case STATE_WIN:         /* … */ break;
                case STATE_GAME_OVER:   /* … */ break;
                case STATE_HIGH_SCORES:
                    DrawHighScores(brickTexture);
                    break;
                default: break;
            }
        }

        EndDrawing();
    }

    // --- Cleanup ---
    FreeMenuSystem();
    unloadRintanganTextures();
    if (rInit) freeRintangan();
    FreeFinishLine(finishList);
    freeCarList(carList);
    UnloadLivesSystem(&livesSystem);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
    UnloadTexture(brickTexture);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
