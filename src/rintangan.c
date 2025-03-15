
#include "../include/rintangan.h"
#include "../include/skor.h"
#include "../include/config.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>

Rintangan rintangan[MAX_LANES][MAX_OBSTACLES];

Skor skor; // Mendeklarasikan objek skor

void initRintangan()
{
    int i, lane, type;

    // Menginisialisasi rintangan di setiap jalur
    for (lane = 0; lane < MAX_LANES; lane++)
    {
        int num_obstacles = 1; // Hanya satu rintangan besar per jalur

        // Mengatur rintangan dengan posisi acak
        for (i = 0; i < num_obstacles; i++)
        {
            rintangan[lane][i].x = (SCREEN_WIDTH / MAX_LANES) * lane + (SCREEN_WIDTH / MAX_LANES) * 0.15; // Lebar jalur dengan offset
            rintangan[lane][i].y = -(rand() % 300 + 100);             // Posisi Y yang lebih aman di layar
            
            // Ukuran yang lebih kecil untuk rintangan
            rintangan[lane][i].width = (SCREEN_WIDTH / MAX_LANES) * 0.7;  // 70% dari lebar jalur
            rintangan[lane][i].height = (SCREEN_HEIGHT / 6);              // Lebih kecil dari sebelumnya
            
            // Tentukan jenis rintangan: kucing, batu, mobil, atau anjing
            type = rand() % 4; // 4 jenis rintangan
            rintangan[lane][i].type = type;

            // Inisialisasi flag
            rintangan[lane][i].hasPassed = false;

            printf("Lane: %d, Obstacle: %d, Type: %d, X: %f, Y: %f\n", lane, i, rintangan[lane][i].type, rintangan[lane][i].x, rintangan[lane][i].y);
        }
    }
}

void drawCat(int x, int y, int width, int height)
{
    // Ukuran proporsional untuk kucing
    int size = fmin(width, height);
    int centerX = x + width/2;
    int centerY = y + height/2;
    
    Color catBody = ORANGE;
    Color catFace = GOLD;
    Color catEar = MAROON;
    
    // Badan kucing (lebih kecil)
    DrawEllipse(centerX, centerY + size/8, size/3, size/4, catBody);
    
    // Kepala kucing
    DrawCircle(centerX, centerY - size/8, size/4, catFace);
    
    // Telinga kucing
    DrawTriangle(
        (Vector2){centerX - size/6, centerY - size/4}, 
        (Vector2){centerX - size/12, centerY - size/2}, 
        (Vector2){centerX, centerY - size/4}, 
        catEar);
    DrawTriangle(
        (Vector2){centerX, centerY - size/4}, 
        (Vector2){centerX + size/12, centerY - size/2}, 
        (Vector2){centerX + size/6, centerY - size/4}, 
        catEar);
    
    // Mata kucing (lebih ekspresif)
    DrawCircle(centerX - size/10, centerY - size/8, size/20, BLACK);
    DrawCircle(centerX + size/10, centerY - size/8, size/20, BLACK);
    
    // Refleksi mata
    DrawCircle(centerX - size/10 + size/60, centerY - size/8 - size/60, size/50, WHITE);
    DrawCircle(centerX + size/10 + size/60, centerY - size/8 - size/60, size/50, WHITE);
    
    // Hidung
    DrawCircle(centerX, centerY, size/20, PINK);
    
    // Mulut
    DrawLine(centerX, centerY + size/40, centerX, centerY + size/12, BLACK);
    DrawLine(centerX, centerY + size/12, centerX - size/15, centerY + size/10, BLACK);
    DrawLine(centerX, centerY + size/12, centerX + size/15, centerY + size/10, BLACK);
    
    // Kumis
    DrawLine(centerX - size/20, centerY, centerX - size/4, centerY - size/30, BLACK);
    DrawLine(centerX - size/20, centerY, centerX - size/4, centerY, BLACK);
    DrawLine(centerX - size/20, centerY, centerX - size/4, centerY + size/30, BLACK);
    
    DrawLine(centerX + size/20, centerY, centerX + size/4, centerY - size/30, BLACK);
    DrawLine(centerX + size/20, centerY, centerX + size/4, centerY, BLACK);
    DrawLine(centerX + size/20, centerY, centerX + size/4, centerY + size/30, BLACK);
    
    // Kaki
    DrawRectangle(centerX - size/4, centerY + size/4, size/12, size/6, catFace);
    DrawRectangle(centerX + size/6, centerY + size/4, size/12, size/6, catFace);
    
    // Ekor
    Vector2 tailPoints[3] = {
        {centerX - size/3, centerY + size/8},
        {centerX - size/2, centerY},
        {centerX - size/2.5, centerY + size/6}
    };
    DrawTriangle(tailPoints[0], tailPoints[1], tailPoints[2], catBody);
}

void drawRock(int x, int y, int width, int height)
{
    // Ukuran proporsional untuk batu
    int size = fmin(width, height);
    int centerX = x + width/2;
    int centerY = y + height/2;
    
    Color rockColor = DARKGRAY;
    Color rockHighlight = GRAY;
    Color rockShadow = BLACK;
    
    // Batu utama
    DrawCircle(centerX, centerY, size/3, rockColor);
    
    // Detil dan tekstur batu
    DrawCircle(centerX - size/6, centerY - size/6, size/10, rockHighlight);
    DrawCircle(centerX + size/8, centerY + size/8, size/12, rockShadow);
    DrawCircle(centerX + size/5, centerY - size/10, size/15, rockHighlight);
    
    // Garis-garis untuk menambah tekstur
    DrawLine(centerX - size/5, centerY, centerX - size/10, centerY + size/6, rockShadow);
    DrawLine(centerX, centerY - size/4, centerX + size/8, centerY - size/10, rockShadow);
    DrawLine(centerX + size/10, centerY, centerX - size/10, centerY + size/8, rockShadow);
}

void drawCar(int x, int y, int width, int height)
{
    // Ukuran proporsional untuk mobil
    int centerX = x + width/2;
    int centerY = y + height/2;
    int carWidth = width * 0.8;  // 80% dari width agar tidak terlalu besar
    int carHeight = height * 0.6; // 60% dari height
    
    Color carBody = RED;
    Color carWindow = SKYBLUE;
    Color carLight = YELLOW;
    Color carWheel = BLACK;
    Color carWheelCap = LIGHTGRAY;
    
    // Badan utama mobil
    DrawRectangleRounded((Rectangle){centerX - carWidth/2, centerY - carHeight/4, carWidth, carHeight/2}, 0.2, 10, carBody);
    
    // Atap mobil
    DrawRectangleRounded((Rectangle){centerX - carWidth/3, centerY - carHeight/2, carWidth*2/3, carHeight/4}, 0.5, 10, carBody);
    
    // Kaca depan
    DrawRectangleRounded((Rectangle){centerX - carWidth/4, centerY - carHeight/2 + carHeight/16, carWidth/2, carHeight/6}, 0.3, 6, carWindow);
    
    // Roda-roda
    float wheelRadius = carHeight/6;
    DrawCircle(centerX - carWidth/3, centerY + carHeight/4, wheelRadius, carWheel);
    DrawCircle(centerX + carWidth/3, centerY + carHeight/4, wheelRadius, carWheel);
    
    // Velg roda
    DrawCircle(centerX - carWidth/3, centerY + carHeight/4, wheelRadius/2, carWheelCap);
    DrawCircle(centerX + carWidth/3, centerY + carHeight/4, wheelRadius/2, carWheelCap);
    
    // Lampu depan
    DrawRectangleRounded((Rectangle){centerX + carWidth/2 - carWidth/12, centerY - carHeight/6, carWidth/12, carHeight/10}, 0.5, 4, carLight);
    
    // Grill
    for (int i = 0; i < 3; i++) {
        DrawLine(
            centerX + carWidth/2 - carWidth/20, 
            centerY - carHeight/12 + i*(carHeight/30),
            centerX + carWidth/2, 
            centerY - carHeight/12 + i*(carHeight/30), 
            BLACK
        );
    }
}

void drawDog(int x, int y, int width, int height)
{
    // Ukuran proporsional untuk anjing
    int size = fmin(width, height);
    int centerX = x + width/2;
    int centerY = y + height/2;
    
    Color dogBody = BEIGE;
    Color dogFace = LIGHTGRAY;
    Color dogNose = BLACK;
    Color dogEar = BROWN;
    
    // Badan anjing
    DrawEllipse(centerX, centerY + size/10, size/3, size/4, dogBody);
    
    // Kepala anjing
    DrawCircle(centerX, centerY - size/6, size/4, dogFace);
    
    // Telinga anjing
    DrawEllipse(centerX - size/5, centerY - size/3, size/10, size/6, dogEar);
    DrawEllipse(centerX + size/5, centerY - size/3, size/10, size/6, dogEar);
    
    // Mata anjing
    DrawCircle(centerX - size/10, centerY - size/6, size/20, BLACK);
    DrawCircle(centerX + size/10, centerY - size/6, size/20, BLACK);
    
    // Refleksi mata
    DrawCircle(centerX - size/10 + size/60, centerY - size/6 - size/60, size/50, WHITE);
    DrawCircle(centerX + size/10 + size/60, centerY - size/6 - size/60, size/50, WHITE);
    
    // Hidung
    DrawCircle(centerX, centerY - size/10, size/15, dogNose);
    
    // Mulut
    DrawLine(centerX, centerY - size/10, centerX, centerY, BLACK);
    DrawLine(centerX - size/15, centerY, centerX, centerY - size/20, BLACK);
    DrawLine(centerX + size/15, centerY, centerX, centerY - size/20, BLACK);
    
    // Lidah
    DrawEllipse(centerX, centerY + size/30, size/25, size/40, PINK);
    
    // Kaki
    DrawRectangle(centerX - size/3, centerY + size/4, size/10, size/8, dogFace);
    DrawRectangle(centerX + size/5, centerY + size/4, size/10, size/8, dogFace);
    
    // Ekor
    Vector2 tailPoints[3] = {
        {centerX - size/3, centerY},
        {centerX - size/2, centerY - size/8},
        {centerX - size/2.5, centerY + size/12}
    };
    DrawTriangle(tailPoints[0], tailPoints[1], tailPoints[2], dogBody);
}

/// rintangan.c
void updateRintangan(Skor *skor, int obstacleSpeed) {
    int lane, i;
    for (lane = 0; lane < MAX_LANES; lane++) {
        for (i = 0; i < MAX_OBSTACLES; i++) {
            // Gerakkan rintangan ke bawah dengan kecepatan sesuai level
            rintangan[lane][i].y += obstacleSpeed;

            // Jika rintangan melewati layar dan belum dihitung
            if (rintangan[lane][i].y > SCREEN_HEIGHT && !rintangan[lane][i].hasPassed) {
                // Tandai rintangan sudah melewati layar
                rintangan[lane][i].hasPassed = true;

                // Tambah skor hanya sekali saat rintangan melewati layar
                tambahSkor(skor, 10);
                printf("Skor ditambah: %d\n", skor->nilai); // Debugging
            }

            // Reset rintangan jika sudah melewati layar
            if (rintangan[lane][i].y > SCREEN_HEIGHT + rintangan[lane][i].height) {
                rintangan[lane][i].y = -(rand() % 300 + 100); // Posisi Y acak di atas layar
                rintangan[lane][i].type = rand() % 4;         // Tipe rintangan acak
                rintangan[lane][i].hasPassed = false;         // Reset flag
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
            int width = rintangan[lane][i].width;
            int height = rintangan[lane][i].height;

            if (rintangan[lane][i].y >= 0) // Pastikan rintangan digambar jika posisi Y valid
            {
                // Menggambar rintangan sesuai tipe
                switch(rintangan[lane][i].type) {
                    case 0:
                        drawCat(x, y, width, height); // Kucing
                        break;
                    case 1:
                        drawRock(x, y, width, height); // Batu
                        break;
                    case 2:
                        drawCar(x, y, width, height); // Mobil
                        break;
                    case 3:
                        drawDog(x, y, width, height); // Anjing
                        break;
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
            if (rintangan[lane][i].y >= 0) // Hanya cek rintangan yang terlihat di layar
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
