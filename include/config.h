#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_LANES 3
#define MAX_OBSTACLES 5

#define PLAYER_CAR_WIDTH 80
#define PLAYER_CAR_HEIGHT 120
#define OBSTACLE_SPEED 5

#define LEFT_LANE_X (SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)
#define MIDDLE_LANE_X (SCREEN_WIDTH / 2 - PLAYER_CAR_WIDTH / 2)
#define RIGHT_LANE_X (3 * SCREEN_WIDTH / 4 - PLAYER_CAR_WIDTH / 2)

#define NUM_CARS 1
#define OBSTACLE_SPEED 5 // Kecepatan rintangan

typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_GAME_OVER,
    STATE_EXIT 
} GameState;

#endif
