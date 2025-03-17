/* ----------------------------------------------------------------------------- */
/* File        : config.h                                                        */
/* Deskripsi   : File header untuk konfigurasi game "C1 Brick Racer".            */
/*              Berisi definisi konstanta, struktur data, dan enum yang digunakan*/
/*              di seluruh game, seperti ukuran layar, state game, level, dll.   */
/* ----------------------------------------------------------------------------- */

#ifndef CONFIG_H
#define CONFIG_H

// Ukuran layar game
#define SCREEN_WIDTH 1280   // Lebar layar dalam piksel
#define SCREEN_HEIGHT 720   // Tinggi layar dalam piksel

// Konfigurasi jalur dan rintangan
#define MAX_LANES 3         // Jumlah jalur yang tersedia
#define MAX_OBSTACLES 5     // Jumlah maksimal rintangan per jalur

// Ukuran mobil pemain
#define PLAYER_CAR_WIDTH  80   // Lebar mobil pemain
#define PLAYER_CAR_HEIGHT 120  // Tinggi mobil pemain

// Kecepatan rintangan
#define OBSTACLE_SPEED 5       // Kecepatan default rintangan

// Posisi jalur (X-coordinate)
#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)    // Posisi jalur kiri
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)  // Posisi jalur tengah
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2) // Posisi jalur kanan

// Jumlah mobil dan kecepatan rintangan
#define NUM_CARS 1             // Jumlah mobil pemain
#define OBSTACLE_SPEED 5       // Kecepatan rintangan

// Konfigurasi garis finish
#define FINISH_LINE_Y 100      // Posisi Y garis finish
#define FINISH_LINE_HEIGHT 10  // Ketebalan garis finish

// Enum untuk state game
typedef enum {
    STATE_MENU,       // State menu utama
    STATE_LEVEL_MENU, // State menu pemilihan level
    STATE_GAME,       // State saat game sedang berjalan
    STATE_COLLISION,  // State saat terjadi tabrakan
    STATE_GAME_OVER,  // State saat game over
    STATE_EXIT        // State untuk keluar dari game
} GameState;

// Konfigurasi level
#define NUM_LEVELS 3                   // Jumlah level yang tersedia
#define MAX_OBSTACLES_PER_LEVEL 10     // Maksimal rintangan per level

// Struktur data untuk level
typedef struct {
    int obstacleSpeed;                 // Kecepatan rintangan di level ini
    int numObstacles;                  // Jumlah rintangan di level ini
    const char* name;                  // Nama level (misalnya, "Easy", "Medium", "Hard")
    Vector2 obstacles[MAX_OBSTACLES_PER_LEVEL]; // Posisi rintangan (array 2D implisit)
} Level;

// Deklarasi array level (definisi ada di file level.c)
extern Level levels[NUM_LEVELS];

#endif