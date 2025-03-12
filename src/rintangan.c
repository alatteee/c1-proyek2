#include "../include/rintangan.h"
#include "../include/skor.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>


Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

Skor skor;  // Mendeklarasikan objek skor

void initRintangan()
{
    int i, lane, type;
    int empty_lane = rand() % MAX_LANES; // Menentukan jalur kosong secara acak

    // Menginisialisasi rintangan di setiap jalur
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        if (lane == empty_lane) {
            continue;  // Lewati jalur kosong
        }

        int num_obstacles = 1; // Hanya satu rintangan besar per jalur

        // Mengatur rintangan dengan posisi acak
        for (i = 0; i < num_obstacles; i++)
        {
            rintangan[lane][i].x = (SCREEN_WIDTH / MAX_LANES) * lane;  // Lebar jalur
            rintangan[lane][i].y = -(rand() % 300 + 100); // Posisi Y yang lebih aman di layar
            rintangan[lane][i].width = SCREEN_WIDTH / MAX_LANES;  // Ukuran lebar rintangan sesuai dengan lebar jalur
            rintangan[lane][i].height = SCREEN_HEIGHT / 5;  // Menyesuaikan tinggi rintangan

            // Tentukan jenis rintangan, misalnya mobil, batu, atau palang
            type = rand() % 3;  // Variasi rintangan
            rintangan[lane][i].type = type;

            printf("Lane: %d, Obstacle: %d, Type: %d, X: %f, Y: %f\n", lane, i, rintangan[lane][i].type, rintangan[lane][i].x, rintangan[lane][i].y);
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
            if (rintangan[lane][i].y > SCREEN_HEIGHT)
            {
                rintangan[lane][i].y = -(rand() % 300 + 100);  // Memberikan jarak antar rintangan
                rintangan[lane][i].type = rand() % 3;  // Variasi tipe rintangan
            }
            else
            {
                rintangan[lane][i].y += OBSTACLE_SPEED;  // Menggerakkan rintangan ke bawah
            }


            if (rintangan[lane][i].y > SCREEN_HEIGHT)
            {
                // Reset posisi jika rintangan keluar dari layar
                rintangan[lane][i].y = -(rand() % 300 + 300);  // Memberikan jarak antar rintangan
                rintangan[lane][i].type = rand() % 3;  // Variasi tipe rintangan
                tambahSkor(&skor, 10);  // Menambah skor jika rintangan melewati pemain
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

            if (rintangan[lane][i].y >= 0)  // Pastikan rintangan digambar jika posisi Y valid
                {
                    // Menggambar rintangan sesuai tipe
                    if (rintangan[lane][i].type == 0)
                    {
                        drawCircle(x + 20, y + 20, 20);  // Batu (coklat)
                    }
                    else if (rintangan[lane][i].type == 1)
                    {
                        drawTriangle(x + 40, y + 40, 40);  // Palang (merah)
                    }
                    else
                    {
                        DrawRectangle(x, y, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, BLUE);  // Mobil (biru)
                    }
                }

        }
    }
}

int checkCollision(float x, float y, float width, float height)
{
    int lane, i;
    
    // Create player rectangle for collision detection
    Rectangle playerRec = {x, y, width, height};

    for (lane = 0; lane < MAX_LANES; lane++)
    {
        for (i = 0; i < MAX_OBSTACLES; i++)
        {
            if (rintangan[lane][i].y >= 0)  // Hanya cek rintangan yang terlihat di layar
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
