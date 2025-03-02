#include "../include/rintangan.h"
#include <stdlib.h>
#include <math.h>

Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

void initRintangan()
{
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
      rintangan[lane][i].x = (SCREEN_WIDTH / MAX_LANES) * lane + (SCREEN_WIDTH / MAX_LANES) / 2 - PLAYER_CAR_WIDTH / 2;
      rintangan[lane][i].y = -(i * 250 + rand() % 100);
      rintangan[lane][i].width = PLAYER_CAR_WIDTH;
      rintangan[lane][i].height = PLAYER_CAR_HEIGHT;

      int type = rand() % 3;
      rintangan[lane][i].type = type;
    }
  }
}

void updateRintangan()
{
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
      rintangan[lane][i].y += 5;
      if (rintangan[lane][i].y > SCREEN_HEIGHT)
      {
        rintangan[lane][i].y = -rand() % 300;
        rintangan[lane][i].type = rand() % 3;
      }
    }
  }
}

void drawCircle(SDL_Renderer *renderer, int x, int y, int r)
{
  for (int w = -r; w < r; w++)
  {
    for (int h = -r; h < r; h++)
    {
      if (w * w + h * h <= r * r)
      {
        SDL_RenderPoint(renderer, x + w, y + h);
        if (rand() % 5 == 0)
          SDL_RenderPoint(renderer, x + w + 2, y + h + 2); // Tekstur kasar
      }
    }
  }
}

void drawTriangle(SDL_Renderer *renderer, int x, int y, int size)
{
  SDL_FPoint points[4] = {
      {x, y - size},
      {x - size / 2, y + size / 2},
      {x + size / 2, y + size / 2},
      {x, y - size}};
  SDL_RenderLines(renderer, points, 4);
  for (int i = -size / 2; i < size / 2; i += 5)
  {
    SDL_RenderPoint(renderer, x + i, y + size / 4); // Garis tekstur
  }
}

void drawRintangan(SDL_Renderer *renderer)
{
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
      int x = rintangan[lane][i].x;
      int y = rintangan[lane][i].y;

      if (rintangan[lane][i].type == 0)
      {
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Batu (coklat)
        drawCircle(renderer, x + 20, y + 20, 20);
      }
      else if (rintangan[lane][i].type == 1)
      {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Palang (merah)
        drawTriangle(renderer, x + 40, y + 40, 40);
      }
      else
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Mobil (biru)
        SDL_FRect obstacle = {x, y, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT};
        SDL_RenderFillRect(renderer, &obstacle);
        for (int j = 0; j < PLAYER_CAR_HEIGHT; j += 5)
        {
          SDL_RenderPoint(renderer, x + PLAYER_CAR_WIDTH / 2, y + j); // Garis tengah
        }
      }
    }
  }
}

bool checkCollision(int carX, int carY, int carWidth, int carHeight)
{
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
      int obsX = rintangan[lane][i].x;
      int obsY = rintangan[lane][i].y;
      int obsWidth = rintangan[lane][i].width;
      int obsHeight = rintangan[lane][i].height;

      if (carX < obsX + obsWidth &&
          carX + carWidth > obsX &&
          carY < obsY + obsHeight &&
          carY + carHeight > obsY)
      {
        return true; // Terjadi tabrakan
      }
    }
  }
  return false; // Tidak ada tabrakan
}
