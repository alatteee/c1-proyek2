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
extern Music menuMusic;
Music gameMusic;

// Deklarasi fungsi helper
MenuNode* FindMenuNodeByState(GameState state);

int main(void) {
    // --- Inisialisasi level --
    List *levelList = LoadDefaultLevels(); 

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
    Texture2D brickTexture = LoadTexture("resources/bg_c1.png");

    // --- Lives ---
    LivesSystem livesSystem = InitLivesSystem(
        (Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);

    // --- Player Car default ---
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
    List *finishList = InitFinishLine();
    bool finishVisible = false;
    float gameTimer = 0.0f;
    bool rInit = false;

    // --- Nama pemain ---
    char playerName[MAX_NAME_LENGTH] = "";

    // --- Inisialisasi menu ---
    InitializeMenuSystem(brickTexture, levelList, carList);
    SetCurrentMenu(STATE_MENU);

    GameState gameState = STATE_MENU;
    bool quit = false;

    // --- Game Loop ---
    while (!quit && !WindowShouldClose()) {
        float dt = GetFrameTime();

        // update musik
        if (isMusicEnabled) {
            UpdateMusicStream(menuMusic);
            UpdateMusicStream(gameMusic);
        }

        // --- Input & State Transisi ---
        if (gameState == STATE_MENU ||
            gameState == STATE_LEVEL_MENU ||
            gameState == STATE_INPUT_NAME ||
            gameState == STATE_SELECT_CAR ||
            gameState == STATE_SETTINGS) {
            HandleMenuInput(&gameState);
            SetCurrentMenu(gameState);
        } else {
            switch (gameState) {
                case STATE_GAME: {
                // Inisialisasi rintangan hanya sekali
                if (!rInit) {
                    initRintangan();
                    rInit = true;
                }

                // Update game timer
                gameTimer += dt;
                if (gameTimer >= 10.0f) {
                    finishVisible = true;
                }

                // Perbaikan utama: Pindahkan inisialisasi mobil ke STATE_GAME pertama kali saja
                static bool carInitialized = false;
                if (!carInitialized) {
                    // Dapatkan data mobil yang dipilih
                    MenuNode* selectCarMenu = FindMenuNodeByState(STATE_SELECT_CAR);
                    if (!selectCarMenu) {
                        TraceLog(LOG_ERROR, "SELECT_CAR menu not found!");
                        gameState = STATE_MENU;
                        break;
                    }
                    
                    CarSelectionData* carData = (CarSelectionData*)selectCarMenu->data;
                    if (!carData || !carData->carList) {
                        TraceLog(LOG_ERROR, "Invalid car selection data!");
                        gameState = STATE_MENU;
                        break;
                    }

                    // Validasi dan load mobil
                    int totalCars = countCars(carData->carList);
                    if (carData->selectedCarIndex >= 0 && carData->selectedCarIndex < totalCars) {
                        CarData *cd = getCarByIndex(carData->carList, carData->selectedCarIndex);
                        if (cd && cd->car.texture.id != 0) {
                            // Hitung aspect ratio
                            float ar = (float)cd->car.texture.width / (float)cd->car.texture.height;
                            float newW = PLAYER_CAR_WIDTH;
                            float newH = newW / ar;
                            
                            // Salin data mobil
                            cars[0] = cd->car;  // Salin seluruh struct
                            cars[0].width = newW;
                            cars[0].height = newH;
                            cars[0].x = MIDDLE_LANE_X;
                            cars[0].y = SCREEN_HEIGHT - newH - 10;
                            
                            TraceLog(LOG_INFO, "Car loaded successfully. Texture ID: %u", cd->car.texture.id);
                        } else {
                            TraceLog(LOG_ERROR, "Invalid car data or texture!");
                            gameState = STATE_MENU;
                            break;
                        }
                    } else {
                        TraceLog(LOG_ERROR, "Invalid car index: %d", carData->selectedCarIndex);
                        gameState = STATE_MENU;
                        break;
                    }
                    carInitialized = true;
                }

                // Update game logic
                handleCarInput(&cars[0]);
                
                // Dapatkan level yang dipilih
                Level *selectedLevel = NULL;
                MenuNode* levelMenu = FindMenuNodeByState(STATE_LEVEL_MENU);
                if (levelMenu) {
                    LevelMenuData* levelData = (LevelMenuData*)levelMenu->data;
                    selectedLevel = getLevelByIndex(levelData->levelList, levelData->selectedLevel);
                }
                
                if (selectedLevel) {
                    updateRintangan(&skor, selectedLevel->obstacleSpeed);
                } else {
                    TraceLog(LOG_WARNING, "No level selected, using default speed");
                    updateRintangan(&skor, 5.0f); // Default speed
                }
                
                // Cek finish line
                if (finishVisible && CheckFinishLineCollision(&cars[0])) {
                    gameState = STATE_WIN;
                }

                // Update invulnerability
                updateCarInvulnerability(&cars[0], dt);
                
                // Cek tabrakan
                if (checkCarObstacleCollision(&cars[0])) {
                    gameState = ReduceLife(&livesSystem) ? STATE_GAME_OVER : STATE_COLLISION;
                }

                break;
            }

                case STATE_COLLISION:
                ClearBackground(DARKGRAY);
                draw_lanes();
                drawRintangan();
                renderCar(&cars[0]);
                tampilkanSkor(&skor);
                DrawLives(livesSystem);

                DrawText("Collision! Press C to continue", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2, 20, RED);

                if (IsKeyPressed(KEY_C)) {
                    cars[0].isInvulnerable = true;
                    cars[0].invulnerabilityTime = 2.0f;
                    gameState = STATE_GAME;
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = STATE_MENU;
                }
                break;


                case STATE_WIN:
                case STATE_GAME_OVER:
                    if (IsKeyPressed(KEY_ENTER)) {
                        InputNameData *in = (InputNameData*)(
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
        ClearBackground(DARKGRAY); // Ganti dengan warna background default

        if (gameState == STATE_WIN || gameState == STATE_GAME_OVER) {
            // Tetap draw background dan elemen game
            DrawTexture(brickTexture, 0, 0, WHITE);
            draw_lanes();
            drawRintangan();
            renderCar(&cars[0]);
            
            // Tambahkan overlay finish
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
                        (Color){0, 0, 0, 180}); // Semi-transparent
            const char* statusText = (gameState == STATE_WIN) ? "YOU WIN!" : "GAME OVER";
            DrawText(statusText, SCREEN_WIDTH/2 - MeasureText(statusText, 40)/2, SCREEN_HEIGHT/2 - 60, 40, WHITE);

            // Tampilkan skor
            char scoreText[64];
            sprintf(scoreText, "Your Score: %d", skor.nilai);
            DrawText(scoreText, SCREEN_WIDTH/2 - MeasureText(scoreText, 20)/2, SCREEN_HEIGHT/2, 20, WHITE);

            // Tambahkan instruksi
            DrawText("Press ENTER to return to menu", 
                    SCREEN_WIDTH/2 - MeasureText("Press ENTER to return to menu", 20)/2,
                    SCREEN_HEIGHT/2 + 40, 20, GRAY);

        } 

        if (gameState == STATE_MENU ||
            gameState == STATE_LEVEL_MENU ||
            gameState == STATE_INPUT_NAME ||
            gameState == STATE_SELECT_CAR ||
            gameState == STATE_SETTINGS) {
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
                case STATE_COLLISION:   /* ... */ break;
                case STATE_WIN:         /* ... */ break;
                case STATE_GAME_OVER:   /* ... */ break;
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
