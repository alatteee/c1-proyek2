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

// Variabel untuk musik
Music menuMusic;
Music gameMusic;
bool isMusicEnabled = true;

int main()
{
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

    // Mainkan musik menu saat game dimulai
    PlayMusicStream(menuMusic);

    // Muat tekstur latar belakang
    Texture2D brickTexture = LoadTexture("resources/coba.jpg");

    // Inisialisasi sistem nyawa
    LivesSystem livesSystem = InitLivesSystem((Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL);

    // Variabel game state
    GameState gameState = STATE_MENU;
    int selectedOption = 0; // Opsi menu yang dipilih
    int selectedLevel = 0;  // Level yang dipilih

    // Inisialisasi mobil pemain
    Car cars[NUM_CARS];
    for (int i = 0; i < NUM_CARS; i++)
    {
        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    }

    // Inisialisasi skor
    Skor skor;
    initSkor(&skor);

    // Variabel untuk input nama pemain
    char playerName[MAX_NAME_LENGTH] = "";

    // Variabel game loop
    bool quit = false;
    bool collisionOccurred = false;
    float gameTimer = 0.0f;         // Timer untuk menghitung waktu permainan
    bool finishLineVisible = false; // Apakah garis finish sudah muncul?

    while (!quit)
    {
        float deltaTime = GetFrameTime(); // Hitung waktu antara frame

        // Update musik jika aktif
        if (isMusicEnabled)
        {
            UpdateMusicStream(menuMusic);
            UpdateMusicStream(gameMusic);
        }

        // Handle input dan update game state
        switch (gameState)
        {
        case STATE_MENU:
            handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
            break;

        case STATE_LEVEL_MENU:
            handleLevelMenuInput(&selectedLevel, &gameState);
            break;

        case STATE_INPUT_NAME:
            // Tangkap input nama pemain
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
                gameState = STATE_GAME; // Mulai permainan
            }
            break;

            case STATE_GAME:
            // Inisialisasi rintangan hanya sekali saat permainan dimulai
            if (!isRintanganInitialized) {
                initRintangan();
                isRintanganInitialized = true; // Set flag menjadi true setelah inisialisasi
            }
        
            // Lanjutkan dengan logika game
            gameTimer += deltaTime;
            if (gameTimer >= 10.0f && !finishLineVisible)
            {
                finishLineVisible = true;
            }
        
            handleCarInput(&cars[0]);
            updateRintangan(&skor, levels[selectedLevel].obstacleSpeed); // Update posisi rintangan
        
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
            // Tunggu pemain menekan ENTER sebelum pindah ke high score
            if (IsKeyPressed(KEY_ENTER))
            {
                SaveHighScore(playerName, skor.nilai); // Simpan skor
                gameState = STATE_HIGH_SCORES; // Pindah ke high score
            }
            break;
        
        case STATE_GAME_OVER:
            // Tunggu pemain menekan ENTER sebelum pindah ke high score
            if (IsKeyPressed(KEY_ENTER))
            {
                SaveHighScore(playerName, skor.nilai); // Simpan skor
                gameState = STATE_HIGH_SCORES; // Pindah ke high score
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
                strcpy(playerName, ""); // Reset nama pemain
            }
            break;

        case STATE_EXIT:
            quit = true;
            break;

        default:
            gameState = STATE_MENU;
            break;
        }

        // Render game
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

        case STATE_INPUT_NAME:
            DrawInputName(playerName, brickTexture);
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
        
            // Tampilkan pesan kemenangan
            DrawText("You Win!", SCREEN_WIDTH / 2 - MeasureText("You Win!", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
            
            // Tampilkan skor di bawahnya
            char skorText[20];  
            sprintf(skorText, "Your Score: %d", skor);
            DrawText(skorText, SCREEN_WIDTH / 2 - MeasureText(skorText, 30) / 2, SCREEN_HEIGHT / 2, 30, YELLOW);
        
            // Tampilkan instruksi untuk melanjutkan
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

    // Unload resources
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
    UnloadTexture(brickTexture);
    UnloadLivesSystem(&livesSystem);
    CloseWindow();
    return 0;
}