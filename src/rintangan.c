// src/rintangan.c
#include "../include/rintangan.h"
#include "../include/double_linked_list.h"
#include <stdlib.h>
#include <time.h>

#define MIN_SPAWN_DELAY 1.0f
#define MAX_SPAWN_DELAY 3.0f

// File names untuk tiap tipe obstacle
static const char *filenames[NUM_OBSTACLE_TYPES] = {
    "resources/obstacle/bebatuan.png",
    "resources/obstacle/bus.png",
    "resources/obstacle/luxury.png",
    "resources/obstacle/mobil1.png",
    "resources/obstacle/mobil2.png",
    "resources/obstacle/truk-sampah.png"
};

static Texture2D obstacleTextures[NUM_OBSTACLE_TYPES];

Lane lanes[MAX_LANES];
bool showCollisionBoxes = false;

// Toggle debug collision box
void toggleCollisionBoxVisibility(void) {
    showCollisionBoxes = !showCollisionBoxes;
}

// Load semua texture obstacle
void loadRintanganTextures(void) {
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        obstacleTextures[i] = LoadTexture(filenames[i]);
    }
}

// Unload texture
void unloadRintanganTextures(void) {
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        UnloadTexture(obstacleTextures[i]);
    }
}

// Buat data obstacle baru
static ObstacleData *createObstacleData(int laneIndex) {
    ObstacleData *d = malloc(sizeof *d);
    int type = rand() % NUM_OBSTACLE_TYPES;
    Texture2D tex = obstacleTextures[type];

    // hitung ukuran dan posisi berdasar lane
    float laneWidth = SCREEN_WIDTH / MAX_LANES;
    float scale     = (laneWidth*0.7f) / tex.width;
    d->width  = tex.width * scale;
    d->height = tex.height * scale;
    float laneX = laneIndex * laneWidth + (laneWidth - d->width)/2;
    d->x = laneX;
    d->y = -d->height - (rand()%200);

    d->type        = type;
    d->texture     = tex;
    d->hasPassed   = false;
    d->hasCollided = false;
    // buat collisionBox sama dengan ukuran scaled
    d->collisionBox = (Rectangle){ d->x, d->y, d->width, d->height };

    return d;
}

// Tambah obstacle ke lane
void addObstacleToLane(int laneIndex) {
    Lane *L = &lanes[laneIndex];
    ObstacleData *d = createObstacleData(laneIndex);
    dl_append(L->obstacles, d);
    // atur spawn time berikutnya
    L->nextSpawnTime = MIN_SPAWN_DELAY +
        ((float)rand()/RAND_MAX)*(MAX_SPAWN_DELAY - MIN_SPAWN_DELAY);
}

void initRintangan(void) {
    srand((unsigned)time(NULL));
    loadRintanganTextures();
    for (int i = 0; i < MAX_LANES; i++) {
        lanes[i].obstacles     = dl_create();
        lanes[i].nextSpawnTime = 0;
        addObstacleToLane(i);
    }
}

// Update obstacle (spawn baru, gerak, count score, remove off-screen)
void updateRintangan(Skor *skor, int speed) {
    float dt = GetFrameTime();
    for (int i = 0; i < MAX_LANES; i++) {
        Lane *L = &lanes[i];
        // spawn jika waktunya
        L->nextSpawnTime -= dt;
        if (L->nextSpawnTime <= 0) addObstacleToLane(i);

        // iterasi manual karena butuh remove
        DLNode *cur = L->obstacles->head;
        while (cur) {
            DLNode *next = cur->next;
            ObstacleData *o = cur->data;
            // gerak turun
            o->y += speed * dt;
            o->collisionBox.y = o->y;
            // scoring
            if (o->y > SCREEN_HEIGHT && !o->hasPassed) {
                o->hasPassed = true;
                skor->nilai += 10;
            }
            // remove jika sudah jauh lewat
            if (o->y > SCREEN_HEIGHT + o->height) {
                dl_remove(L->obstacles, cur, free);
            }
            cur = next;
        }
    }
}

// Draw satu obstacle
static void _drawOne(void *data) {
    ObstacleData *o = data;
    DrawTexturePro(
        o->texture,
        (Rectangle){0,0,o->texture.width,o->texture.height},
        (Rectangle){o->x,o->y,o->width,o->height},
        (Vector2){0,0}, 0.0f, WHITE
    );
}

// Draw semua rintangan + optional collision box
void drawRintangan(void) {
    for (int i = 0; i < MAX_LANES; i++) {
        dl_for_each(lanes[i].obstacles, _drawOne);
    }
    if (showCollisionBoxes) {
        // gambar kotak merah untuk debug
        for (int i = 0; i < MAX_LANES; i++) {
            DLNode *cur = lanes[i].obstacles->head;
            while (cur) {
                ObstacleData *o = cur->data;
                DrawRectangleLines(
                    o->collisionBox.x, o->collisionBox.y,
                    o->collisionBox.width, o->collisionBox.height,
                    RED
                );
                cur = cur->next;
            }
        }
    }
}

// Check collision player & obstacle, return count hits
int checkCollision(float x, float y, float w, float h) {
    int hits = 0;
    Rectangle player = { x, y, w, h };
    for (int i = 0; i < MAX_LANES; i++) {
        DLNode *cur = lanes[i].obstacles->head;
        while (cur) {
            ObstacleData *o = cur->data;
            if (!o->hasCollided &&
                CheckCollisionRecs(player, o->collisionBox)) {
                o->hasCollided = true;
                hits++;
            }
            cur = cur->next;
        }
    }
    return hits;
}

// Free semua
void freeRintangan(void) {
    for (int i = 0; i < MAX_LANES; i++) {
        dl_destroy(lanes[i].obstacles, free);
    }
    unloadRintanganTextures();
}
