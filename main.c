#include <raylib.h>
#include "include/mobil.h"
#include "include/menu.h"
#include "include/jalur.h"
#include "include/rintangan.h"
#include "include/skor.h"
#include "include/config.h"

#define NUM_CARS 1  // Jumlah mobil pemain
#define MOVE_STEP 1 // Langkah perpindahan mobil

// Koordinat jalur untuk mobil
#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2) 
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

#define NUM_LANES 3        // Tetap dengan 3 jalur
#define LANE_WIDTH 200     // Lebar jalur menjadi 200 piksel

int main()
{
    // Inisialisasi Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Racing Game");

    // Inisialisasi mobil pemain
    Car cars[NUM_CARS];
    int i;
    for (i = 0; i < NUM_CARS; i++)
    {
        initCar(&cars[i], MIDDLE_LANE_X, SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f - (i * 100), PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    }

    // Inisialisasi rintangan
    initRintangan();

    // Inisialisasi skor
    Skor skor;
    initSkor(&skor);

    bool quit = false;
    
    // Nyawa pemain
    int lives = 3;

    while (!quit)
    {
        // Handle input events
        if (IsKeyPressed(KEY_ESCAPE)) quit = true;

        // Pergerakan mobil
        if (IsKeyDown(KEY_LEFT)) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].x > LEFT_LANE_X) {
                    cars[i].x -= cars[i].speed;
                    cars[i].rect.x = cars[i].x;
                }
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].x < RIGHT_LANE_X) {
                    cars[i].x += cars[i].speed;
                    cars[i].rect.x = cars[i].x;
                }
            }
        }
        if (IsKeyDown(KEY_UP)) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].y > 0) {
                    cars[i].y -= cars[i].speed;
                    cars[i].rect.y = cars[i].y;
                }
            }
        }
        if (IsKeyDown(KEY_DOWN)) {
            for (i = 0; i < NUM_CARS; i++) {
                if (cars[i].y + cars[i].height < SCREEN_HEIGHT) {
                    cars[i].y += cars[i].speed;
                    cars[i].rect.y = cars[i].y;
                }
            }
        }

        // Memperbarui posisi rintangan
        updateRintangan();

        // Mengecek tabrakan antara mobil dan rintangan
        for (i = 0; i < NUM_CARS; i++) {
            if (checkCollision(cars[i].x, cars[i].y, cars[i].width, cars[i].height)) {
                lives--; // Mengurangi nyawa jika terjadi tabrakan
                kurangiSkor(&skor, 10);  // Kurangi skor jika menabrak rintangan

                if (lives <= 0) {
                    DrawText("Game Over!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, RED);
                    DrawText(TextFormat("Your score: %d", getSkor(&skor)), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 30, 20, RED);
                    quit = true; // Akhiri permainan jika nyawa habis
                }
                else {
                    // Reset posisi mobil jika terjadi tabrakan
                    cars[i].x = MIDDLE_LANE_X;
                    cars[i].y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10;
                }
            }
        }

        // Menggambar ulang layar
        BeginDrawing();
        ClearBackground(BLACK);

        // Menggambar jalur
        draw_lanes();

        // Menggambar rintangan
        drawRintangan();

        // Menggambar mobil pemain
        for (i = 0; i < NUM_CARS; i++) {
            renderCar(&cars[i]);
        }

        // Menampilkan skor di layar
        tampilkanSkor(&skor);

        EndDrawing();
    }

    // Membersihkan Raylib sebelum keluar
    CloseWindow(); // Tutup window dan berhenti Raylib

    return 0;
}
