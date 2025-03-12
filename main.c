
#include <SDL3/SDL.h>
#include "include/SDL_ttf.h"
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/config.h" // Include config.h

#define NUM_CARS 1  // Jumlah mobil pemain
#define MOVE_STEP 1 // Langkah perpindahan mobil

// Koordinat jalur untuk mobil
#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

int main()
{
  // Inisialisasi SDL
  SDL_Init(SDL_INIT_VIDEO);

    // Membuat jendela permainan
    SDL_Window *window = SDL_CreateWindow("Racing Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
      SDL_Log("Failed to create window: %s", SDL_GetError());
      SDL_Quit();
      return 1;
    }
  
    // Membuat renderer untuk menggambar objek permainan
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
      SDL_Log("Failed to create renderer: %s", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }

  bool menuRunning = true;
  SDL_Event e;

  // Loop untuk menunggu input dari pengguna
  while (menuRunning)
  {
      while (SDL_PollEvent(&e) != 0)
      {
          if (e.type == SDL_EVENT_QUIT)
          {
              menuRunning = false;
          }

          if (e.type == SDL_EVENT_KEY_DOWN)
          {
              if (e.key.scancode == SDL_SCANCODE_RETURN)
              {
                  menuRunning = false; // Keluar dari menu dan lanjutkan permainan
              }
          }
      }
      // Render ulang menu di setiap frame
      showMenu(renderer);
  }

  // Inisialisasi mobil pemain
  Car cars[NUM_CARS];
  int i;
  for (i = 0; i < NUM_CARS; i++)
  {
    initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f - (i * 100), PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
  }

  // Inisialisasi rintangan
  initRintangan();

  bool quit = false;
  SDL_Event b;

  // Nyawa pemain
  int lives = 3;

  while (!quit)
  {
    // Menangani event (input dari pemain)
    while (SDL_PollEvent(&b) != 0)
    {
      if (b.type == SDL_EVENT_QUIT)
      {
        quit = true;
      }
    }

    // Membaca input keyboard
    const Uint8 *currentKeyStates = (const Uint8 *)SDL_GetKeyboardState(NULL);

    // Pergerakan mobil ke kiri
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
      for (i = 0; i < NUM_CARS; i++)
      {
        if (cars[i].x > LEFT_LANE_X)
        {
          cars[i].x = LEFT_LANE_X;
          cars[i].rect.x = cars[i].x;
        }
      }
    }

    // Pergerakan mobil ke kanan
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
      for (i = 0; i < NUM_CARS; i++)
      {
        if (cars[i].x < RIGHT_LANE_X)
        {
          cars[i].x = RIGHT_LANE_X;
          cars[i].rect.x = cars[i].x;
        }
      }
    }

    // Pergerakan mobil ke atas (maju)
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
      for (i = 0; i < NUM_CARS; i++)
      {
        if (cars[i].y > 0) // Jangan keluar layar atas
        {
          cars[i].y -= cars[i].speed;
          cars[i].rect.y = cars[i].y;
        }
      }
    }

    // Pergerakan mobil ke bawah (mundur)
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
      for (i = 0; i < NUM_CARS; i++)
      {
        if (cars[i].y + cars[i].height < SCREEN_HEIGHT) // Jangan keluar layar bawah
        {
          cars[i].y += cars[i].speed;
          cars[i].rect.y = cars[i].y;
        }
      }
    }

    // Memperbarui posisi rintangan
    updateRintangan();

    // Mengecek tabrakan antara mobil dan rintangan
    for (i = 0; i < NUM_CARS; i++)
    {
      if (checkCollision(cars[i].x, cars[i].y, cars[i].width, cars[i].height))
      {
        lives--; // Mengurangi nyawa jika terjadi tabrakan
        if (lives <= 0)
        {
          SDL_Log("Game Over!");
          quit = true; // Akhiri permainan jika nyawa habis
        }
        else
        {
          SDL_Log("You hit an obstacle! You have %d lives left.", lives);
          // Reset posisi mobil jika terjadi tabrakan
          cars[i].x = MIDDLE_LANE_X;
          cars[i].y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10;
        }
      }
    }

    // Menggambar ulang layar
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Menggambar jalur
    draw_lanes(renderer);

    // Menggambar rintangan
    drawRintangan(renderer);

    // Menggambar mobil pemain
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < NUM_CARS; i++)
    {
      renderCar(renderer, &cars[i]);
    }

    // Menampilkan hasil render ke layar
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // Memberikan jeda untuk frame rate yang lebih stabil
  }

  // Membersihkan SDL sebelum keluar
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
