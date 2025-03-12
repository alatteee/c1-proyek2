#include "../include/rintangan.h"
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

void initRintangan()
{
    int i, lane, type;

    // Menginisialisasi rintangan di setiap jalur
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        // Tentukan beberapa jalur yang akan memiliki rintangan
        int num_obstacles = rand() % (MAX_OBSTACLES / 2); // Setengah dari MAX_OBSTACLES

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

void drawCircle(int x, int y, int r)
{
    // Menggambar lingkaran rintangan
    DrawCircle(x, y, r, BROWN); // Batu (coklat)
}

void drawTriangle(int x, int y, int size)
{
    // Menggambar segitiga untuk jenis rintangan palang
    Vector2 points[3] = {
        {x, y - size},
        {x - size / 2, y + size / 2},
        {x + size / 2, y + size / 2}
    };
    DrawTriangle(points[0], points[1], points[2], RED); // Palang (merah)
}

void updateRintangan()
{
    int lane, i;
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            if (rintangan[lane][i].y > 0) // Cek apakah rintangan ada di layar
            {
                rintangan[lane][i].y += 5; // Gerakkan ke bawah
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

void drawRintangan()
{
    int lane, i, x, y;
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            x = rintangan[lane][i].x;
            y = rintangan[lane][i].y;

            if (rintangan[lane][i].y > 0) // Hanya menggambar rintangan yang masih di layar
            {
                if (rintangan[lane][i].type == 0)
                {
                    // Batu (coklat)
                    drawCircle(x + 20, y + 20, 20);
                }
                else if (rintangan[lane][i].type == 1)
                {
                    // Palang (merah)
                    drawTriangle(x + 40, y + 40, 40);
                }
                else
                {
                    // Mobil (biru)
                    DrawRectangle(x, y, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, BLUE);
                }
            }
        }
    }
}

// Fungsi baru yang perlu ditambahkan
int checkCollision(float x, float y, float width, float height)
{
    int lane, i;
    
    // Create player rectangle for collision detection
    Rectangle playerRec = {x, y, width, height};

    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            if (rintangan[lane][i].y > 0) // Hanya cek rintangan yang terlihat di layar
            {
                // Create obstacle rectangle for collision detection
                Rectangle obstacleRec = {rintangan[lane][i].x, rintangan[lane][i].y, rintangan[lane][i].width, rintangan[lane][i].height};

                // Cek tabrakan
                if (CheckCollisionRecs(playerRec, obstacleRec))
                {
                    return 1; // Terjadi tabrakan
                }
            }
        }
    }

    return 0; // Tidak ada tabrakan
}
