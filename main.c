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


// Variabel musik
Music menuMusic;
Music gameMusic;
bool isMusicEnabled = true;

int main()
{

    LevelNode* levelList = NULL;
    AppendLevel(&levelList, "Easy", 5);
    AppendLevel(&levelList, "Medium", 8);
    AppendLevel(&levelList, "Hard", 12);

    // Inisialisasi window dan audio
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer");
    SetTargetFPS(60);
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

    // Inisialisasi mobil pemain
    Car cars[NUM_CARS];
    initCar(&cars[0], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10,
            PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10, "resources/mobil/biasa_kuning.png");

    // Inisialisasi linked list pilihan mobil
    CarNode *carList = createCarList();
    int selectedCarIndex = 0;
    int totalCars = countCars(carList);

    // Inisialisasi skor
    Skor skor;
    initSkor(&skor);

    // Variabel input nama
    char playerName[MAX_NAME_LENGTH] = "";

    // Game loop
    bool quit = false;
    bool collisionOccurred = false;
    float gameTimer = 0.0f;
    bool finishLineVisible = false;

    while (!quit && !WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (isMusicEnabled)
        {
            UpdateMusicStream(menuMusic);
            UpdateMusicStream(gameMusic);
        }

        // Handle input
        switch (gameState)
        {
        case STATE_MENU:
            handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
            break;

        case STATE_LEVEL_MENU:
            handleLevelMenuInput(&selectedLevel, &gameState);
            break;

        case STATE_INPUT_NAME:
            {
                int key = GetCharPressed();
                if (key > 0 && strlen(playerName) < MAX_NAME_LENGTH - 1)
                {
                    playerName[strlen(playerName)] = (char)key;
                }
                if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0)
                {
                    playerName[strlen(playerName) - 1] = '\0';
                }
                if (IsKeyPressed(KEY_ENTER) && strlen(playerName) > 0)
                {
                    gameState = STATE_SELECT_CAR; // setelah isi nama, lanjut pilih mobil
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
                CarNode *selectedCarNode = getCarByIndex(carList, selectedCarIndex);
                cars[0] = selectedCarNode->car; // Copy mobil terpilih
                cars[0].x = MIDDLE_LANE_X;
                cars[0].y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10;
                gameState = STATE_GAME; // setelah pilih mobil, langsung ke game
            }
            break;

        case STATE_GAME:
            if (!isRintanganInitialized)
            {
                initRintangan();
                isRintanganInitialized = true;
            }

            gameTimer += deltaTime;
            if (gameTimer >= 10.0f && !finishLineVisible)
            {
                finishLineVisible = true;
            }

            handleCarInput(&cars[0]);
            LevelNode* currentLevel = getLevelByIndex(levelList, selectedLevel);
            if (currentLevel != NULL) {
                updateRintangan(&skor, currentLevel->obstacleSpeed);
            }


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
                                rintangan[lane][j].height};

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

        case STATE_COLLISION:
            if (IsKeyPressed(KEY_C))
                gameState = STATE_GAME;
            if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
                gameState = STATE_MENU;
            break;

        case STATE_WIN:
        case STATE_GAME_OVER:
            if (IsKeyPressed(KEY_ENTER))
            {
                SaveHighScore(playerName, skor.nilai);
                gameState = STATE_HIGH_SCORES;
            }
            break;

        case STATE_HIGH_SCORES:
            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = STATE_MENU;
                ResetLives(&livesSystem);
                initSkor(&skor);
                gameTimer = 0.0f;
                finishLineVisible = false;
                strcpy(playerName, "");
            }
            break;

        case STATE_EXIT:
            quit = true;
            break;

        default:
            gameState = STATE_MENU;
            break;
        }

        // Render
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState)
        {
        case STATE_MENU:
            DrawMenu(selectedOption, brickTexture);
            break;

        case STATE_LEVEL_MENU:
            DrawLevelMenu(selectedLevel, brickTexture, levelList);
            break;

        case STATE_INPUT_NAME:
            DrawInputName(playerName, brickTexture);
            break;

        case STATE_SELECT_CAR:
            drawCarSelection(carList, selectedCarIndex, brickTexture);
            break;
        
        case STATE_GAME:
            ClearBackground(DARKGRAY);
            draw_lanes();
            if (finishLineVisible)
                DrawFinishLine();
            drawRintangan();
            renderCar(&cars[0]);
            tampilkanSkor(&skor);
            DrawLives(livesSystem);
            break;

        case STATE_COLLISION:
            ClearBackground(DARKGRAY);
            draw_lanes();
            drawRintangan();
            renderCar(&cars[0]);
            tampilkanSkor(&skor);
            DrawLives(livesSystem);
            DrawText("Collision Detected!", SCREEN_WIDTH / 2 - MeasureText("Collision Detected!", 30) / 2, SCREEN_HEIGHT / 2 - 50, 30, RED);
            DrawText("Press C to Continue, Q/ESC to Quit", SCREEN_WIDTH / 2 - MeasureText("Press C to Continue, Q/ESC to Quit", 20) / 2, SCREEN_HEIGHT / 2, 20, WHITE);
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

    // Unload semua resource
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
    UnloadTexture(brickTexture);
    UnloadLivesSystem(&livesSystem);
    freeCarList(carList);
    FreeLevels(levelList);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
