#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_LANES 3
#define MAX_OBSTACLES 5

#define PLAYER_CAR_WIDTH 80   // Lebar mobil
#define PLAYER_CAR_HEIGHT 120 // Tinggi mobil
#define OBSTACLE_SPEED 5

#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

#define NUM_CARS 1
#define OBSTACLE_SPEED 5 // Kecepatan rintangan

#define MAX_NAME_LENGTH 20
#define MAX_HIGH_SCORES 10

typedef enum
{
    STATE_MENU,
    STATE_LEVEL_MENU,
    STATE_INPUT_NAME, // Tambahkan state untuk input nama
    STATE_GAME,
    STATE_COLLISION,
    STATE_WIN,
    STATE_GAME_OVER,
    STATE_HIGH_SCORES, // Tambahkan state untuk high scores
    STATE_EXIT
} GameState;

#define NUM_LEVELS 3 // Jumlah level yang tersedia

typedef struct
{
    int obstacleSpeed;    // Kecepatan rintangan
    int numObstacles;     // Jumlah rintangan
    const char *name;     // Nama level
    int positions[10][2]; // Posisi rintangan
} Level;

extern Level levels[NUM_LEVELS];


#endif