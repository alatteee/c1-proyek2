#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/config.h"
#include "include/jalur.h"
#include "include/menu.h"
#include "include/mobil.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/lives.h"
#include "include/high_score.h"
#include "include/finish_line.h"
#include "include/level.h"
#include "include/mobil_selection.h"

// Variabel musik global
Music menuMusic;
Music gameMusic;
bool isMusicEnabled = true;

// FIXED: Tambahkan fungsi helper untuk reset complete game state
void resetCompleteGameState(bool *isRintanganInitialized, float *gameTimer, bool *finishLineVisible, 
                           LivesSystem *livesSystem, Skor *skor, Car *car) {
    // 1. Cleanup rintangan yang ada
    if (*isRintanganInitialized) {
        freeRintangan();
        *isRintanganInitialized = false;
    }
    
    // 2. Reset semua timer dan flag
    *gameTimer = 0.0f;
    *finishLineVisible = false;
    
    // 3. Reset lives system
    ResetLives(livesSystem);
    
    // 4. Reset skor
    resetSkor(skor);
    
    // 5. Reset car invulnerability
    car->isInvulnerable = false;
    car->invulnerabilityTime = 0.0f;
    
    // 6. Reset car position ke default
    car->x = MIDDLE_LANE_X;
    car->y = SCREEN_HEIGHT - car->height - 10;
    car->currentLane = LANE_MIDDLE;
    car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// FIXED: Tambahkan fungsi untuk switch music berdasarkan state
void updateMusicForState(GameState gameState) {
    if (!isMusicEnabled) {
        StopMusicStream(menuMusic);
        StopMusicStream(gameMusic);
        return;
    }
    
    if (gameState == STATE_GAME) {
        if (!IsMusicStreamPlaying(gameMusic)) {
            StopMusicStream(menuMusic);
            PlayMusicStream(gameMusic);
        }
        UpdateMusicStream(gameMusic);
    } else {
        if (!IsMusicStreamPlaying(menuMusic)) {
            StopMusicStream(gameMusic);
            PlayMusicStream(menuMusic);
        }
        UpdateMusicStream(menuMusic);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);

    // Level list - menggunakan single linked list
    List *levelList = createLevelList();

    InitAudioDevice();

    bool isRintanganInitialized = false;

    // Muat musik
    menuMusic = LoadMusicStream("resources/menusound.mp3");
    gameMusic = LoadMusicStream("resources/racingcarsound.mp3");
    SetMusicVolume(menuMusic, 1.5f);
    SetMusicVolume(gameMusic, 1.5f);
    PlayMusicStream(menuMusic);

    // Muat tekstur latar belakang
    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    // Inisialisasi sistem nyawa
    LivesSystem livesSystem = InitLivesSystem((Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);

    // Variabel game state
    GameState gameState = STATE_MENU;
    int selectedOption = 0;
    int selectedLevel = 0;
    int selectedSettingsOption = 0;

    // Inisialisasi mobil pemain
    Car cars[NUM_CARS];
    initCar(&cars[0], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10,
            PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10, "resources/mobil/biasa_kuning.png");

    // Inisialisasi linked list pilihan mobil
    List *carList = createCarList();
    int selectedCarIndex = 0;
    int totalCars = countCars(carList);

    // Inisialisasi skor
    Skor skor;
    initSkor(&skor);

    // Variabel input nama
    char playerName[MAX_NAME_LENGTH] = "";

    // Game loop
    bool quit = false;
    float gameTimer = 0.0f;
    bool finishLineVisible = false;

    while (!quit && !WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_F1)) {
            toggleCollisionBoxVisibility();
        }

        // FIXED: Update music berdasarkan state
        updateMusicForState(gameState);

        switch (gameState) {
        case STATE_MENU:
            // FIXED: Reset semua game state saat masuk menu
            if (isRintanganInitialized || gameTimer > 0 || finishLineVisible || 
                livesSystem.currentLives != MAX_LIVES || getSkor(&skor) > 0) {
                resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                     &livesSystem, &skor, &cars[0]);
            }
            handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
            break;

        case STATE_SETTINGS:
            handleSettingsInput(&selectedSettingsOption, &gameState);
            break;

        case STATE_LEVEL_MENU:
            handleLevelMenuInput(&selectedLevel, &gameState, levelList);
            break;

        case STATE_INPUT_NAME: {
            int key = GetCharPressed();
            if (key > 0 && strlen(playerName) < MAX_NAME_LENGTH - 1) {
                playerName[strlen(playerName)] = (char)key;
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0) {
                playerName[strlen(playerName) - 1] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && strlen(playerName) > 0) {
                gameState = STATE_SELECT_CAR;
            }
        }
        break;

        case STATE_SELECT_CAR:
            if (IsKeyPressed(KEY_UP)) {
                selectedCarIndex--;
                if (selectedCarIndex < 0)
                    selectedCarIndex = totalCars - 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                selectedCarIndex++;
                if (selectedCarIndex >= totalCars)
                    selectedCarIndex = 0;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                CarData *selectedCarNode = getCarByIndex(carList, selectedCarIndex);

                Texture2D selectedTexture = selectedCarNode->car.texture;
                float aspectRatio = (float)selectedTexture.width / (float)selectedTexture.height;
                float newWidth = PLAYER_CAR_WIDTH;
                float newHeight = newWidth / aspectRatio;

                cars[0] = selectedCarNode->car;
                cars[0].width = newWidth;
                cars[0].height = newHeight;
                cars[0].x = MIDDLE_LANE_X;
                cars[0].y = SCREEN_HEIGHT - newHeight - 10;
                cars[0].currentLane = LANE_MIDDLE;

                // FIXED: FORCE RESET semua game state saat start game baru
                // Ini memastikan tidak ada state yang tersisa dari game sebelumnya
                resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                     &livesSystem, &skor, &cars[0]);
                
                // Update car position lagi setelah reset
                cars[0].x = MIDDLE_LANE_X;
                cars[0].y = SCREEN_HEIGHT - newHeight - 10;
                cars[0].currentLane = LANE_MIDDLE;
                
                printf("=== STARTING NEW GAME ===\n");
                printf("Player: %s, Level: %d\n", playerName, selectedLevel);
                printf("Game state completely reset\n");
                
                gameState = STATE_GAME;
            }
            break;

        case STATE_GAME:
            // FIXED: SELALU reset rintangan saat pertama masuk STATE_GAME
            if (!isRintanganInitialized) {
                printf("Initializing fresh obstacle system...\n");
                initRintangan();
                isRintanganInitialized = true;
            }

            gameTimer += deltaTime;
            if (gameTimer >= 10.0f && !finishLineVisible) {
                finishLineVisible = true;
                printf("Finish line now visible!\n");
            }

            handleCarInput(&cars[0]);

            LevelData *currentLevel = getLevelByIndex(levelList, selectedLevel);
            if (currentLevel != NULL) {
                updateRintangan(&skor, currentLevel->obstacleSpeed);
            }

            updateCarInvulnerability(&cars[0], deltaTime);

            if (!cars[0].isInvulnerable) {
                int collision = checkCollision(cars[0].x, cars[0].y, cars[0].width, cars[0].height);
                if (collision > 0) {
                    cars[0].isInvulnerable = true;
                    cars[0].invulnerabilityTime = INVULNERABILITY_DURATION;
                    gameState = STATE_COLLISION;
                }
            }

            if (finishLineVisible && CheckFinishLineCollision(&cars[0])) {
                SaveHighScore(playerName, getSkor(&skor));
                gameState = STATE_WIN;
            }
            break;

        case STATE_COLLISION:
            if (IsKeyPressed(KEY_C)) {
                bool gameOver = ReduceLife(&livesSystem);
                
                if (gameOver) {
                    SaveHighScore(playerName, getSkor(&skor));
                    gameState = STATE_GAME_OVER;
                } else {
                    gameState = STATE_GAME;
                }
            }
            if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) {
                SaveHighScore(playerName, getSkor(&skor));
                // FIXED: Reset state saat quit dari collision
                resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                     &livesSystem, &skor, &cars[0]);
                gameState = STATE_MENU;
                printf("Quit to menu - game state reset\n");
            }
            break;

        case STATE_WIN:
            if (IsKeyPressed(KEY_ENTER)) {
                // FIXED: Reset state saat win
                resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                     &livesSystem, &skor, &cars[0]);
                gameState = STATE_MENU;
                printf("Win screen - returning to menu\n");
            }
            break;

        case STATE_GAME_OVER:
            if (IsKeyPressed(KEY_ENTER)) {
                // FIXED: Reset state saat game over
                resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                     &livesSystem, &skor, &cars[0]);
                gameState = STATE_MENU;
                printf("Game over - returning to menu\n");
            }
            break;

        case STATE_HIGH_SCORES:
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
                gameState = STATE_MENU;
            }
            break;

        case STATE_EXIT:
            // FIXED: Final cleanup sebelum quit
            resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                                 &livesSystem, &skor, &cars[0]);
            quit = true;
            break;

        default:
            break;
        }

        BeginDrawing();

        switch (gameState) {
        case STATE_MENU:
            DrawMenu(selectedOption, brickTexture);
            break;

        case STATE_SETTINGS:
            DrawSettingsMenu(selectedSettingsOption, brickTexture);
            break;

        case STATE_LEVEL_MENU:
            DrawLevelMenu(selectedLevel, brickTexture, levelList);
            break;

        case STATE_INPUT_NAME:
            DrawInputName(playerName, brickTexture);
            break;

        case STATE_SELECT_CAR:
            ClearBackground(DARKGRAY);
            drawCarSelection(carList, selectedCarIndex, brickTexture);
            break;

        case STATE_GAME:
            ClearBackground(DARKGRAY);
            draw_lanes();
            if (finishLineVisible) {
                DrawFinishLine();
            }
            drawRintangan();
            drawCollisionBoxes(true, cars[0].x, cars[0].y, cars[0].width, cars[0].height);
            renderCar(&cars[0]);
            tampilkanSkor(&skor);
            DrawLives(livesSystem);
            
            // FIXED: Tambah debug info untuk tracking state
            char debugInfo[100];
            snprintf(debugInfo, sizeof(debugInfo), "Timer: %.1f | Obstacles: %s | Score: %d", 
                    gameTimer, isRintanganInitialized ? "INIT" : "NULL", getSkor(&skor));
            DrawText(debugInfo, 10, SCREEN_HEIGHT - 40, 12, YELLOW);
            DrawText("Press F1 for debug view", 10, SCREEN_HEIGHT - 20, 10, GRAY);
            break;

        case STATE_COLLISION:
            ClearBackground(DARKGRAY);
            draw_lanes();
            drawRintangan();
            drawCollisionBoxes(true, cars[0].x, cars[0].y, cars[0].width, cars[0].height);
            renderCar(&cars[0]);
            tampilkanSkor(&skor);
            DrawLives(livesSystem);
            DrawText("Collision Detected!", SCREEN_WIDTH / 2 - MeasureText("Collision Detected!", 30) / 2, SCREEN_HEIGHT / 2 - 50, 30, RED);
            
            char livesInfo[50];
            snprintf(livesInfo, sizeof(livesInfo), "Lives remaining: %d", livesSystem.currentLives);
            DrawText(livesInfo, SCREEN_WIDTH / 2 - MeasureText(livesInfo, 20) / 2, SCREEN_HEIGHT / 2 - 10, 20, YELLOW);
            
            DrawText("Press C to Continue, Q/ESC to Quit", SCREEN_WIDTH / 2 - MeasureText("Press C to Continue, Q/ESC to Quit", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
            break;

        case STATE_WIN:
            ClearBackground(DARKGRAY);
            draw_lanes();
            DrawFinishLine();
            drawRintangan();
            renderCar(&cars[0]);
            tampilkanSkor(&skor);
            DrawLives(livesSystem);
            DrawText("You Win!", SCREEN_WIDTH / 2 - MeasureText("You Win!", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
            DrawText("Press ENTER to continue", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to continue", 20) / 2, SCREEN_HEIGHT / 2 + 50, 20, WHITE);
            break;

        case STATE_GAME_OVER:
            ClearBackground(BLACK);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
            DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
            break;

        case STATE_HIGH_SCORES:
            DrawHighScores(brickTexture);
            break;

        default:
            break;
        }

        EndDrawing();
    }

    // FIXED: Final cleanup sebelum program berakhir
    resetCompleteGameState(&isRintanganInitialized, &gameTimer, &finishLineVisible, 
                         &livesSystem, &skor, &cars[0]);
    
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
    UnloadTexture(brickTexture);
    UnloadLivesSystem(&livesSystem);
    freeCarList(carList);
    freeLevelList(levelList);
    freeSkor(&skor);

    unloadRintanganTextures();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}