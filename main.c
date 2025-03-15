#include <raylib.h>
#include <stdio.h>
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"
#include "include/lives.h"
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

  while (!quit)
  {
    // Tambahkan pengecekan jika window close diminta (misalnya klik [X] pada jendela)
    if (WindowShouldClose())
    {
      quit = true;
    }

    float deltaTime = GetFrameTime();

    switch (gameState)
    {
    case STATE_MENU:
      handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor);
      // Tekan ESC di menu untuk keluar
      if (IsKeyPressed(KEY_ESCAPE))
      {
        gameState = STATE_EXIT;
      }
      break;

    case STATE_LEVEL_MENU:
      handleLevelMenuInput(&selectedLevel, &gameState);
      break;

    case STATE_GAME:
    {
      Level currentLevel = levels[selectedLevel];
      handleCarInput(&cars[0]);
      updateRintangan(&skor, currentLevel.obstacleSpeed);

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
              Rectangle obstacle = {rintangan[lane][j].x, rintangan[lane][j].y,
                                    rintangan[lane][j].width, rintangan[lane][j].height};
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
      // Di state collision, pemain dapat menekan:
      // C untuk Lanjut (continue)
      // Q atau ESC untuk kembali ke menu
      if (IsKeyPressed(KEY_C))
      {
        gameState = STATE_GAME;
      }
      if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
      {
        gameState = STATE_MENU;
      }
      break;

    case STATE_GAME_OVER:
      if (IsKeyPressed(KEY_ENTER))
      {
        gameState = STATE_MENU;
        ResetLives(&livesSystem);
        initSkor(&skor);
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
      drawRintangan();
      for (int i = 0; i < NUM_CARS; i++)
      {
        renderCar(&cars[i]);
      }
      tampilkanSkor(&skor);
      DrawLives(livesSystem);
      break;

    case STATE_COLLISION:
      ClearBackground(DARKGRAY);
      draw_lanes();
      drawRintangan();
      for (int i = 0; i < NUM_CARS; i++)
      {
        renderCar(&cars[i]);
      }
      tampilkanSkor(&skor);
      DrawLives(livesSystem);
      DrawText("Collision Detected!", SCREEN_WIDTH / 2 - MeasureText("Collision Detected!", 30) / 2,
               SCREEN_HEIGHT / 2 - 50, 30, RED);
      DrawText("Press C to Continue, Q/ESC to Quit", SCREEN_WIDTH / 2 - MeasureText("Press C to Continue, Q/ESC to Quit", 20) / 2,
               SCREEN_HEIGHT / 2, 20, WHITE);
      break;

    case STATE_GAME_OVER:
      ClearBackground(BLACK);
      DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
      DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2,
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