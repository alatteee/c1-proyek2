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
Music menuMusic;            // Musik untuk menu utama
Music gameMusic;            // Musik untuk permainan
bool isMusicEnabled = true; // Status musik (aktif atau tidak)

int main()
{
  // Inisialisasi window dan audio
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C1 Brick Racer"); // Inisialisasi jendela permainan
  SetTargetFPS(60);                                          // Set FPS untuk permainan menjadi 60
  InitAudioDevice();                                         // Inisialisasi perangkat audio
  bool isRintanganInitialized = false;                       // Flag untuk mengecek apakah rintangan sudah diinisialisasi

  // Muat musik
  menuMusic = LoadMusicStream("resources/menusound.mp3");      // Musik untuk menu
  gameMusic = LoadMusicStream("resources/racingcarsound.mp3"); // Musik untuk permainan
  SetMusicVolume(menuMusic, 1.5f);                             // Set volume musik menu
  SetMusicVolume(gameMusic, 1.5f);                             // Set volume musik permainan

  // Mainkan musik menu saat game dimulai
  PlayMusicStream(menuMusic); // Memutar musik menu

  // Muat tekstur latar belakang
  Texture2D brickTexture = LoadTexture("resources/coba.jpg"); // Memuat gambar latar belakang

  // Inisialisasi sistem nyawa
  LivesSystem livesSystem = InitLivesSystem((Vector2){SCREEN_WIDTH - 150, 10}, 40.0f, 30.0f, NULL); // Inisialisasi sistem nyawa

  // Variabel game state
  GameState gameState = STATE_MENU; // Set state permainan awal ke menu
  int selectedOption = 0;           // Opsi menu yang dipilih (default 0)
  int selectedLevel = 0;            // Level yang dipilih (default 0)

  // Inisialisasi mobil pemain
  Car cars[NUM_CARS]; // Array untuk menyimpan mobil
  for (int i = 0; i < NUM_CARS; i++)
  {
    initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10); // Inisialisasi mobil pemain
  }

  // Inisialisasi skor
  Skor skor;
  initSkor(&skor); // Inisialisasi skor

  // Variabel untuk input nama pemain
  char playerName[MAX_NAME_LENGTH] = ""; // Nama pemain yang dimasukkan

  // Variabel game loop
  bool quit = false;              // Flag untuk keluar dari game
  bool collisionOccurred = false; // Flag untuk mengecek apakah terjadi tabrakan
  float gameTimer = 0.0f;         // Timer untuk menghitung waktu permainan
  bool finishLineVisible = false; // Apakah garis finish sudah muncul?

  // Game loop
  while (!quit)
  {
    float deltaTime = GetFrameTime(); // Hitung waktu antara frame

    // Update musik jika aktif
    if (isMusicEnabled)
    {
      UpdateMusicStream(menuMusic); // Update musik menu
      UpdateMusicStream(gameMusic); // Update musik permainan
    }

    // Handle input dan update game state
    switch (gameState)
    {
    case STATE_MENU:
      handleMenuInput(&selectedOption, &gameState, cars, &livesSystem.currentLives, &skor); // Handle input menu
      break;

    case STATE_LEVEL_MENU:
      handleLevelMenuInput(&selectedLevel, &gameState); // Handle input level menu
      break;

    case STATE_INPUT_NAME:
      // Tangkap input nama pemain
      int key = GetCharPressed(); // Ambil karakter yang ditekan
      if (key > 0 && strlen(playerName) < MAX_NAME_LENGTH - 1)
      {
        playerName[strlen(playerName)] = (char)key; // Tambahkan karakter ke nama pemain
      }
      if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerName) > 0)
      {
        playerName[strlen(playerName) - 1] = '\0'; // Hapus karakter terakhir dari nama pemain
      }
      if (IsKeyPressed(KEY_ENTER) && strlen(playerName) > 0)
      {
        gameState = STATE_GAME; // Mulai permainan jika nama sudah dimasukkan
      }
      break;

    case STATE_GAME:
      // Inisialisasi rintangan hanya sekali saat permainan dimulai
      if (!isRintanganInitialized)
      {
        initRintangan();               // Inisialisasi rintangan
        isRintanganInitialized = true; // Set flag menjadi true setelah inisialisasi
      }

      // Lanjutkan dengan logika game
      gameTimer += deltaTime; // Tambah waktu permainan
      if (gameTimer >= 10.0f && !finishLineVisible)
      {
        finishLineVisible = true; // Tampilkan garis finish setelah 10 detik
      }

      handleCarInput(&cars[0]);                                    // Handle input mobil
      updateRintangan(&skor, levels[selectedLevel].obstacleSpeed); // Update posisi rintangan

      if (finishLineVisible && CheckFinishLineCollision(&cars[0]))
      {
        gameState = STATE_WIN; // Jika pemain melewati garis finish, lanjut ke state menang
      }

      collisionOccurred = false; // Reset flag collision
      for (int i = 0; i < NUM_CARS && !collisionOccurred; i++)
      {
        updateCarInvulnerability(&cars[i], deltaTime); // Update invulnerability mobil
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
              if (checkCarCollision(&cars[i], obstacle)) // Cek tabrakan antara mobil dan rintangan
              {
                if (ReduceLife(&livesSystem)) // Kurangi nyawa jika tabrakan terjadi
                {
                  gameState = STATE_GAME_OVER; // Game over jika nyawa habis
                }
                else
                {
                  gameState = STATE_COLLISION; // Pindah ke state tabrakan
                }
                collisionOccurred = true; // Set flag collision menjadi true
              }
            }
          }
        }
      }
      break;

    case STATE_COLLISION:
      if (IsKeyPressed(KEY_C))
        gameState = STATE_GAME; // Lanjutkan permainan jika pemain menekan C
      if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
        gameState = STATE_MENU; // Kembali ke menu jika pemain menekan Q atau ESC
      break;

    case STATE_WIN:
      // Tunggu pemain menekan ENTER sebelum pindah ke high score
      if (IsKeyPressed(KEY_ENTER))
      {
        SaveHighScore(playerName, skor.nilai); // Simpan skor jika pemain menang
        gameState = STATE_HIGH_SCORES;         // Pindah ke high score
      }
      break;

    case STATE_GAME_OVER:
      // Tunggu pemain menekan ENTER sebelum pindah ke high score
      if (IsKeyPressed(KEY_ENTER))
      {
        SaveHighScore(playerName, skor.nilai); // Simpan skor jika game over
        gameState = STATE_HIGH_SCORES;         // Pindah ke high score
      }
      break;

    case STATE_HIGH_SCORES:
      if (IsKeyPressed(KEY_ENTER))
      {
        gameState = STATE_MENU;    // Kembali ke menu jika pemain menekan ENTER
        ResetLives(&livesSystem);  // Reset nyawa
        initSkor(&skor);           // Reset skor
        gameTimer = 0.0f;          // Reset timer permainan
        finishLineVisible = false; // Reset status garis finish
        strcpy(playerName, "");    // Reset nama pemain
      }
      break;

    case STATE_EXIT:
      quit = true; // Keluar dari permainan
      break;

    default:
      gameState = STATE_MENU; // Jika state tidak dikenali, kembali ke menu
      break;
    }

    // Render game
    BeginDrawing();            // Mulai menggambar
    ClearBackground(RAYWHITE); // Bersihkan latar belakang

    // Draw sesuai dengan game state
    switch (gameState)
    {
    case STATE_MENU:
      DrawMenu(selectedOption, brickTexture); // Gambar menu
      break;

    case STATE_LEVEL_MENU:
      DrawLevelMenu(selectedLevel, brickTexture); // Gambar menu level
      break;

    case STATE_INPUT_NAME:
      DrawInputName(playerName, brickTexture); // Gambar input nama
      break;

    case STATE_GAME:
      ClearBackground(DARKGRAY); // Bersihkan latar belakang saat game
      draw_lanes();              // Gambar jalur
      if (finishLineVisible)
        DrawFinishLine();     // Gambar garis finish jika sudah terlihat
      drawRintangan();        // Gambar rintangan
      renderCar(&cars[0]);    // Gambar mobil
      tampilkanSkor(&skor);   // Tampilkan skor
      DrawLives(livesSystem); // Tampilkan nyawa
      break;

    case STATE_COLLISION:
      ClearBackground(DARKGRAY);                                                                                                                                  // Bersihkan latar belakang saat terjadi tabrakan
      draw_lanes();                                                                                                                                               // Gambar jalur
      drawRintangan();                                                                                                                                            // Gambar rintangan
      renderCar(&cars[0]);                                                                                                                                        // Gambar mobil
      tampilkanSkor(&skor);                                                                                                                                       // Tampilkan skor
      DrawLives(livesSystem);                                                                                                                                     // Tampilkan nyawa
      DrawText("Collision Detected!", SCREEN_WIDTH / 2 - MeasureText("Collision Detected!", 30) / 2, SCREEN_HEIGHT / 2 - 50, 30, RED);                            // Tampilkan pesan tabrakan
      DrawText("Press C to Continue, Q/ESC to Quit", SCREEN_WIDTH / 2 - MeasureText("Press C to Continue, Q/ESC to Quit", 20) / 2, SCREEN_HEIGHT / 2, 20, WHITE); // Instruksi untuk lanjut atau keluar
      break;

    case STATE_WIN:
      ClearBackground(DARKGRAY); // Bersihkan latar belakang saat pemain menang
      draw_lanes();              // Gambar jalur
      DrawFinishLine();          // Gambar garis finish
      drawRintangan();           // Gambar rintangan
      renderCar(&cars[0]);       // Gambar mobil

      tampilkanSkor(&skor);   // Tampilkan skor
      DrawLives(livesSystem); // Tampilkan nyawa

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
      ClearBackground(BLACK);                                                                                                                                // Bersihkan latar belakang saat game over
      DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);                                           // Tampilkan pesan game over
      DrawText("Press ENTER to return to Menu", SCREEN_WIDTH / 2 - MeasureText("Press ENTER to return to Menu", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE); // Instruksi untuk kembali ke menu
      break;

    case STATE_HIGH_SCORES:
      DrawHighScores(brickTexture); // Tampilkan high scores
      break;

    default:
      break;
    }
    EndDrawing(); // Selesai menggambar
  }

  // Unload resources
  UnloadMusicStream(menuMusic);    // Unload musik menu
  UnloadMusicStream(gameMusic);    // Unload musik game
  UnloadTexture(brickTexture);     // Unload tekstur latar belakang
  UnloadLivesSystem(&livesSystem); // Unload sistem nyawa
  CloseWindow();                   // Tutup window
  return 0;                        // Selesai
}
