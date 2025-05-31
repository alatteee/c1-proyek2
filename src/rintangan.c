#include "../include/rintangan.h"
#include "../include/skor.h"
#include "../include/config.h"
#include "../include/double_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <raylib.h>

// Lanes untuk obstacle
Lane lanes[MAX_LANES];

// Debug mode untuk collision boxes
bool showCollisionBoxes = false;

// Definisi untuk obstacle spawning
#define MIN_OBSTACLE_DISTANCE 600
#define MIN_SPAWN_DELAY 1.0f
#define MAX_SPAWN_DELAY 3.0f
#define MAX_OBSTACLES_PER_LANE 5

// Array untuk menyimpan textures untuk obstacle
#define NUM_OBSTACLE_TYPES 6
Texture2D obstacleTextures[NUM_OBSTACLE_TYPES];

const char *obstacleFilenames[NUM_OBSTACLE_TYPES] = {
    "resources/obstacle/bebatuan.png",
    "resources/obstacle/bus.png",
    "resources/obstacle/luxury.png",
    "resources/obstacle/mobil1.png",
    "resources/obstacle/mobil2.png",
    "resources/obstacle/truk-sampah.png"};

typedef struct
{
  float offsetXPercent;
  float offsetYPercent;
  float widthPercent;
  float heightPercent;
  float sizeScale;
} ObstacleSpec;

// Definisi spec untuk setiap jenis obstacle
ObstacleSpec obstacleSpecs[NUM_OBSTACLE_TYPES] = {
    // offsetX, offsetY, widthPercent, heightPercent, sizeScale
    {0.25, 0.20, 0.50, 0.60, 0.33},  // bebatuan
    {0.30, 0.08, 0.40, 0.85, 0.88},  // bus
    {0.30, 0.15, 0.40, 0.70, 0.605}, // luxury
    {0.30, 0.15, 0.40, 0.70, 0.605}, // mobil1
    {0.30, 0.15, 0.40, 0.70, 0.605}, // mobil2
    {0.30, 0.15, 0.40, 0.70, 0.88}   // truk sampah
};

// Fungsi untuk toggle collision box visibility
void toggleCollisionBoxVisibility()
{
  showCollisionBoxes = !showCollisionBoxes;
  printf("Debug visualization: %s\n", showCollisionBoxes ? "ON" : "OFF");
}

// Fungsi untuk memuat texture rintangan
void loadRintanganTextures()
{
  for (int i = 0; i < NUM_OBSTACLE_TYPES; i++)
  {
    obstacleTextures[i] = LoadTexture(obstacleFilenames[i]);

    if (obstacleTextures[i].id > 0)
    {
      printf("Texture %d loaded successfully: %dx%d\n",
             i, obstacleTextures[i].width, obstacleTextures[i].height);
    }
    else
    {
      printf("Failed to load texture %d: %s\n", i, obstacleFilenames[i]);
    }
  }
}

// Fungsi untuk melepaskan texture rintangan
void unloadRintanganTextures()
{
  for (int i = 0; i < NUM_OBSTACLE_TYPES; i++)
  {
    UnloadTexture(obstacleTextures[i]);
  }
  printf("All obstacle textures unloaded\n");
}

// Fungsi untuk membuat obstacle data
ObstacleData *createObstacleData(int laneIndex)
{
  ObstacleData *newData = (ObstacleData *)malloc(sizeof(ObstacleData));
  if (newData == NULL)
  {
    printf("Error: Failed to allocate memory for obstacle data\n");
    return NULL;
  }

  int type = rand() % NUM_OBSTACLE_TYPES;

  float laneWidth = SCREEN_WIDTH / MAX_LANES;
  float maxObstacleWidth = laneWidth * 0.7f;

  float baseScale = maxObstacleWidth / obstacleTextures[type].width;
  float finalScale = baseScale * obstacleSpecs[type].sizeScale;

  float obstacleWidth = obstacleTextures[type].width * finalScale;
  float obstacleHeight = obstacleTextures[type].height * finalScale;

  float laneCenter = laneIndex * laneWidth + laneWidth / 2;
  float obstacleX = laneCenter - obstacleWidth / 2;

  float obstacleY = -obstacleHeight - (rand() % 300);

  if (lanes[laneIndex].obstacles && lanes[laneIndex].obstacles->tail)
  {
    ObstacleData *lastObstacle = (ObstacleData *)lanes[laneIndex].obstacles->tail->data;
    float lastObstacleY = lastObstacle->y;
    if (obstacleY > lastObstacleY - MIN_OBSTACLE_DISTANCE)
    {
      obstacleY = lastObstacleY - MIN_OBSTACLE_DISTANCE - (rand() % 200);
    }
  }

  float collisionX = obstacleX + (obstacleWidth * obstacleSpecs[type].offsetXPercent);
  float collisionY = obstacleY + (obstacleHeight * obstacleSpecs[type].offsetYPercent);
  float collisionWidth = obstacleWidth * obstacleSpecs[type].widthPercent;
  float collisionHeight = obstacleHeight * obstacleSpecs[type].heightPercent;

  newData->x = obstacleX;
  newData->y = obstacleY;
  newData->width = obstacleWidth;
  newData->height = obstacleHeight;
  newData->type = type;
  newData->hasPassed = false;
  newData->hasCollided = false;
  newData->texture = obstacleTextures[type];
  newData->collisionBox = (Rectangle){
      collisionX,
      collisionY,
      collisionWidth,
      collisionHeight};

  return newData;
}

// Fungsi untuk menambahkan obstacle ke lane
void addObstacleToLane(int laneIndex)
{
  // Jangan tambahkan obstacle jika sudah mencapai batas
  if (lanes[laneIndex].obstacleCount >= MAX_OBSTACLES_PER_LANE)
  {
    return;
  }

  ObstacleData *newData = createObstacleData(laneIndex);
  if (newData == NULL)
    return;

  dl_append(lanes[laneIndex].obstacles, newData);
  lanes[laneIndex].obstacleCount++;
}

// Fungsi untuk membebaskan memori obstacle data
void freeObstacleData(void *data)
{
  if (data)
  {
    free(data);
  }
}

// Fungsi untuk menghapus obstacle dari lane
void removeObstacleFromLane(int laneIndex, DLNode *node)
{
  if (!lanes[laneIndex].obstacles || !node)
    return;

  dl_remove(lanes[laneIndex].obstacles, node, freeObstacleData);
  lanes[laneIndex].obstacleCount--;
}

// Fungsi untuk inisialisasi sistem rintangan
void initRintangan()
{
  srand((unsigned int)time(NULL));

  static bool texturesLoaded = false;
  if (!texturesLoaded)
  {
    loadRintanganTextures();
    texturesLoaded = true;
  }

  for (int i = 0; i < MAX_LANES; i++)
  {
    lanes[i].obstacles = dl_create();
    lanes[i].obstacleCount = 0;
    lanes[i].nextSpawnTime = (float)(rand() % 100) / 100.0f;

    addObstacleToLane(i);
    if (lanes[i].obstacles && lanes[i].obstacles->head)
    {
      ObstacleData *data = (ObstacleData *)lanes[i].obstacles->head->data;
      data->y = -300 - i * 400;
    }
  }
}

// Fungsi untuk membersihkan semua obstacle
void freeRintangan()
{
  for (int i = 0; i < MAX_LANES; i++)
  {
    if (lanes[i].obstacles)
    {
      dl_destroy(lanes[i].obstacles, freeObstacleData);
      lanes[i].obstacles = NULL;
    }
    lanes[i].obstacleCount = 0;
  }
}

// Fungsi untuk update posisi obstacle dan spawn obstacle baru
void updateRintangan(Skor *skor, int obstacleSpeed)
{
  float deltaTime = GetFrameTime();

  // Update spawn timers untuk setiap lane
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    lanes[lane].nextSpawnTime -= deltaTime;

    if (lanes[lane].nextSpawnTime <= 0 && lanes[lane].obstacleCount < MAX_OBSTACLES_PER_LANE)
    {
      addObstacleToLane(lane);

      float randomDelay = MIN_SPAWN_DELAY + ((float)rand() / RAND_MAX) * (MAX_SPAWN_DELAY - MIN_SPAWN_DELAY);
      lanes[lane].nextSpawnTime = randomDelay;
    }

    if (!lanes[lane].obstacles)
      continue;

    DLNode *current = lanes[lane].obstacles->head;
    while (current != NULL)
    {
      DLNode *next = current->next;

      ObstacleData *data = (ObstacleData *)current->data;

      data->y += obstacleSpeed;

      data->collisionBox.x = data->x + (data->width * obstacleSpecs[data->type].offsetXPercent);
      data->collisionBox.y = data->y + (data->height * obstacleSpecs[data->type].offsetYPercent);

      if (data->y > SCREEN_HEIGHT && !data->hasPassed)
      {
        data->hasPassed = true;
        skor->nilai += 10;
      }

      if (data->y > SCREEN_HEIGHT + data->height)
      {
        dl_remove(lanes[lane].obstacles, current, freeObstacleData);
        lanes[lane].obstacleCount--;
      }

      current = next;
    }
  }
}

// Fungsi untuk menggambar obstacle (helper function untuk dl_for_each)
void drawObstacle(void *data)
{
  ObstacleData *obstacle = (ObstacleData *)data;

  if (obstacle->y >= -obstacle->height)
  {
    DrawTexturePro(
        obstacle->texture,
        (Rectangle){0, 0, obstacle->texture.width, obstacle->texture.height},
        (Rectangle){
            obstacle->x,
            obstacle->y,
            obstacle->width,
            obstacle->height},
        (Vector2){0, 0},
        0.0f,
        WHITE);

    if (showCollisionBoxes)
    {
      DrawRectangleLines(
          obstacle->collisionBox.x,
          obstacle->collisionBox.y,
          obstacle->collisionBox.width,
          obstacle->collisionBox.height,
          RED);
    }
  }
}

// Fungsi untuk menggambar semua obstacle
void drawRintangan()
{
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    if (lanes[lane].obstacles)
    {
      dl_for_each(lanes[lane].obstacles, drawObstacle);
    }
  }
}

// Fungsi untuk menggambar collision boxes
void drawCollisionBoxes(bool drawPlayerBox, float x, float y, float width, float height)
{
  if (!showCollisionBoxes)
    return;

  // Gambar collision box untuk player
  if (drawPlayerBox)
  {
    float playerMarginX = width * 0.25;
    float playerMarginY = height * 0.10;

    Rectangle playerRec = {
        x + playerMarginX,
        y + playerMarginY,
        width * 0.50,
        height * 0.80};

    DrawRectangleLines(playerRec.x, playerRec.y, playerRec.width, playerRec.height, BLUE);
  }
}

// Fungsi untuk memeriksa tabrakan
int checkCollision(float x, float y, float width, float height)
{
  int collisionCount = 0;

  // Collision box untuk player
  float playerMarginX = width * 0.25;
  float playerMarginY = height * 0.10;

  Rectangle playerRec = {
      x + playerMarginX,
      y + playerMarginY,
      width * 0.50,
      height * 0.80};

  // Periksa collision dengan semua obstacle
  for (int lane = 0; lane < MAX_LANES; lane++)
  {
    if (!lanes[lane].obstacles)
      continue;

    DLNode *current = lanes[lane].obstacles->head;
    while (current != NULL)
    {
      ObstacleData *data = (ObstacleData *)current->data;

      if (data->y >= 0 && !data->hasCollided)
      {
        if (CheckCollisionRecs(playerRec, data->collisionBox))
        {
          data->hasCollided = true;
          collisionCount++;
        }
      }

      current = current->next;
    }
  }

  return collisionCount;
}
