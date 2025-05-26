#ifndef CONFIG_H
#define CONFIG_H

// Definisi lebar layar permainan
#define SCREEN_WIDTH 1280
// Definisi tinggi layar permainan
#define SCREEN_HEIGHT 720

// Definisi jumlah jalur yang tersedia untuk mobil pemain
#define MAX_LANES 3
// Definisi jumlah maksimum rintangan yang bisa ada di layar
#define MAX_OBSTACLES 5

// Definisi ukuran mobil pemain (lebar dan tinggi) - naik 15%
#define PLAYER_CAR_WIDTH 115   // Lebar mobil (100 + 15%)
#define PLAYER_CAR_HEIGHT 161  // Tinggi mobil (140 + 15%)

// Posisi X untuk jalur - mobil tetap di tengah jalur yang sama
#define LEFT_LANE_X (SCREEN_WIDTH / 6 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (5 * SCREEN_WIDTH / 6 - PLAYER_CAR_WIDTH / 2)

#define NUM_CARS 1           // Jumlah mobil pemain (hanya 1 mobil)
#define OBSTACLE_SPEED 5     // Kecepatan rintangan yang muncul

// Definisi panjang maksimal nama pemain dalam high scores
#define MAX_NAME_LENGTH 20
// Definisi jumlah high scores yang bisa disimpan
#define MAX_HIGH_SCORES 10

// Enum untuk lane position
typedef enum
{
    LANE_LEFT = 0,
    LANE_MIDDLE = 1,
    LANE_RIGHT = 2
} LanePosition;

// Enum yang mendefinisikan status permainan (menu, level, game over, dll)
typedef enum
{
    STATE_MENU,            // Menu utama permainan
    STATE_LEVEL_MENU,      // Menu untuk memilih level permainan
    STATE_INPUT_NAME,      // Menu untuk memasukkan nama pemain
    STATE_GAME,            // Status permainan saat sedang berjalan
    STATE_COLLISION,       // Status ketika terjadi tabrakan
    STATE_WIN,             // Status ketika pemain menang
    STATE_GAME_OVER,       // Status ketika permainan berakhir
    STATE_HIGH_SCORES,     // Menu untuk menampilkan skor tertinggi
    STATE_SETTINGS,        // Menu settings
    STATE_EXIT,          // Status keluar dari permainan
    STATE_SELECT_CAR
} GameState;

#define NUM_LEVELS 3        // Jumlah level yang tersedia dalam permainan

// Struktur yang mendefinisikan setiap level permainan
typedef struct
{
    int obstacleSpeed;    // Kecepatan rintangan di level ini
    int numObstacles;     // Jumlah rintangan yang ada di level ini
    const char *name;     // Nama level (misalnya: "Level 1")
    int positions[10][2]; // Posisi rintangan (koordinat X dan Y) di level ini
} Level;

#endif