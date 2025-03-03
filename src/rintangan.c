#include "../include/rintangan.h"
#include <stdlib.h>
#include <math.h>

Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

void initRintangan()
{
    int i, lane, type;

    // Menginisialisasi rintangan di setiap jalur
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        // Tentukan beberapa jalur yang akan memiliki rintangan
        int num_obstacles = rand() % (MAX_OBSTACLES / 2);  // Setengah dari MAX_OBSTACLES

        // Mengacak interval rintangan agar muncul bergiliran
        for (i = 0; i < num_obstacles; i++)
        {
            // Tentukan apakah rintangan ini muncul di jalur yang sudah ada sebelumnya
            if (rand() % 2 == 0)
            {
                rintangan[lane][i].x = (SCREEN_WIDTH / MAX_LANES) * lane + (SCREEN_WIDTH / MAX_LANES) / 2 - PLAYER_CAR_WIDTH / 2;
                rintangan[lane][i].y = -(i * 250 + rand() % 100);
                rintangan[lane][i].width = PLAYER_CAR_WIDTH;
                rintangan[lane][i].height = PLAYER_CAR_HEIGHT;

                // Tentukan tipe rintangan secara acak
                type = rand() % 3;
                rintangan[lane][i].type = type;
            }
        }
    }
}
void drawCircle(SDL_Renderer *renderer, int x, int y, int r)
{
    int w, h;
    for (w = -r; w < r; w++)
    {
        for (h = -r; h < r; h++)
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
    int i;
    SDL_FPoint points[4] = {
        {x, y - size},
        {x - size / 2, y + size / 2},
        {x + size / 2, y + size / 2},
        {x, y - size}};
    SDL_RenderLines(renderer, points, 4);
    for (i = -size / 2; i < size / 2; i += 5)
    {
        SDL_RenderPoint(renderer, x + i, y + size / 4); // Garis tekstur
    }
}


void updateRintangan()
{
    int lane, i;
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            if (rintangan[lane][i].y > 0)  // Cek apakah rintangan ada di layar
            {
                rintangan[lane][i].y += 5;  // Gerakkan ke bawah
            }

            if (rintangan[lane][i].y > SCREEN_HEIGHT)
            {
                // Reset posisi jika rintangan keluar dari layar
                rintangan[lane][i].y = -rand() % 300;

                // Tentukan tipe rintangan baru secara acak
                rintangan[lane][i].type = rand() % 3;

                // Tentukan apakah rintangan muncul kembali di jalur yang sama atau tidak
                if (rand() % 2 == 0)
                {
                    rintangan[lane][i].x = (SCREEN_WIDTH / MAX_LANES) * lane + (SCREEN_WIDTH / MAX_LANES) / 2 - PLAYER_CAR_WIDTH / 2;
                }
            }
        }
    }
}

void drawRintangan(SDL_Renderer *renderer)
{
    int lane, i, x, y, j;
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            x = rintangan[lane][i].x;
            y = rintangan[lane][i].y;

            if (rintangan[lane][i].y > 0)  // Hanya menggambar rintangan yang masih di layar
            {
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
                    for (j = 0; j < PLAYER_CAR_HEIGHT; j += 5)
                    {
                        SDL_RenderPoint(renderer, x + PLAYER_CAR_WIDTH / 2, y + j); // Garis tengah
                    }
                }
            }
        }
    }
}
