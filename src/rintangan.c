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
static bool texturesLoaded = false;

Lane lanes[MAX_LANES];
bool showCollisionBoxes = false;

// Toggle debug collision box
void toggleCollisionBoxVisibility(void) {
    showCollisionBoxes = !showCollisionBoxes;
}

// Load semua texture obstacle
void loadRintanganTextures(void) {
    if (texturesLoaded) return;
    
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        obstacleTextures[i] = LoadTexture(filenames[i]);
        if (obstacleTextures[i].id == 0) {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filenames[i]);
        } else {
            TraceLog(LOG_INFO, "Loaded texture %d: %s (ID: %u)", 
                   i, filenames[i], obstacleTextures[i].id);
        }
    }
    texturesLoaded = true;
}

// Unload texture
void unloadRintanganTextures(void) {
    if (!texturesLoaded) return;
    
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        if (obstacleTextures[i].id != 0) {
            UnloadTexture(obstacleTextures[i]);
            obstacleTextures[i].id = 0;
        }
    }
    texturesLoaded = false;
}

// Buat data obstacle baru
static ObstacleData *createObstacleData(int laneIndex) {
    ObstacleData *d = malloc(sizeof *d);
    if (!d) return NULL;

    int type = rand() % NUM_OBSTACLE_TYPES;
    
    // Hitung ukuran dan posisi berdasar lane
    float laneWidth = SCREEN_WIDTH / MAX_LANES;
    float scale = (laneWidth*0.7f) / obstacleTextures[type].width;
    
    d->width  = obstacleTextures[type].width * scale;
    d->height = obstacleTextures[type].height * scale;
    d->x = laneIndex * laneWidth + (laneWidth - d->width)/2;
    d->y = -d->height - (rand()%200);

    d->type        = type;
    d->texture     = obstacleTextures[type]; // Reference ke texture utama
    d->hasPassed   = false;
    d->hasCollided = false;
    d->collisionBox = (Rectangle){ d->x, d->y, d->width, d->height };

    return d;
}

// Tambah obstacle ke lane
void addObstacleToLane(int laneIndex) {
    if (laneIndex < 0 || laneIndex >= MAX_LANES) return;
    
    Lane *L = &lanes[laneIndex];
    ObstacleData *d = createObstacleData(laneIndex);
    if (!d) return;

    if (!L->obstacles) {
        L->obstacles = dl_create();
    }
    
    dl_append(L->obstacles, d);
    L->nextSpawnTime = MIN_SPAWN_DELAY + 
                      ((float)rand()/RAND_MAX)*(MAX_SPAWN_DELAY - MIN_SPAWN_DELAY);
}

void initRintangan(void) {
    srand((unsigned)time(NULL));
    
    // Inisialisasi lanes
    for (int i = 0; i < MAX_LANES; i++) {
        lanes[i].obstacles = NULL;
        lanes[i].nextSpawnTime = 0;
    }
    
    // Load textures jika belum
    if (!texturesLoaded) {
        loadRintanganTextures();
    }
    
    // Tambah obstacle awal
    for (int i = 0; i < MAX_LANES; i++) {
        addObstacleToLane(i);
    }
}

// Update obstacle (spawn baru, gerak, count score, remove off-screen)
void updateRintangan(Skor *skor, int speed) {
    float dt = GetFrameTime();
    
    for (int i = 0; i < MAX_LANES; i++) {
        Lane *L = &lanes[i];
        if (!L->obstacles) continue;

        // Spawn obstacle baru jika waktunya
        L->nextSpawnTime -= dt;
        if (L->nextSpawnTime <= 0) {
            addObstacleToLane(i);
        }

        // Update existing obstacles
        DLNode *cur = L->obstacles->head;
        while (cur) {
            DLNode *next = cur->next;
            ObstacleData *o = cur->data;
            
            if (!o) {
                cur = next;
                continue;
            }

            // Gerak obstacle
            o->y += speed * dt;
            o->collisionBox.y = o->y;

            // Scoring
            if (o->y > SCREEN_HEIGHT && !o->hasPassed) {
                o->hasPassed = true;
                if (skor) skor->nilai += 10;
            }

            // Remove jika sudah lewat layar
            if (o->y > SCREEN_HEIGHT + o->height) {
                dl_remove(L->obstacles, cur, free);
            }
            
            cur = next;
        }
    }
}

// Draw satu obstacle
static void _drawOne(void *data) {
    ObstacleData *o = (ObstacleData*)data;
    if (!o || o->texture.id == 0) return;

    DrawTexturePro(
        o->texture,
        (Rectangle){0,0,o->texture.width,o->texture.height},
        (Rectangle){o->x,o->y,o->width,o->height},
        (Vector2){0,0}, 0.0f, WHITE
    );
}

// Draw semua rintangan + optional collision box
void drawRintangan(void) {
    TraceLog(LOG_INFO, "Drawing obstacles...");
    
    for (int i = 0; i < MAX_LANES; i++) {
        if (!lanes[i].obstacles) {
            TraceLog(LOG_WARNING, "Lane %d has no obstacles list", i);
            continue;
        }
        
        DLNode *cur = lanes[i].obstacles->head;
        while (cur) {
            ObstacleData *o = cur->data;
            if (!o) {
                TraceLog(LOG_WARNING, "Null obstacle in lane %d", i);
                cur = cur->next;
                continue;
            }
            
            TraceLog(LOG_DEBUG, "Drawing obstacle at (%.1f, %.1f) with texture ID %u", 
                   o->x, o->y, o->texture.id);
            
            if (o->texture.id == 0) {
                TraceLog(LOG_ERROR, "Invalid texture in obstacle!");
            } else {
                DrawTexturePro(o->texture, 
                    (Rectangle){0,0,o->texture.width,o->texture.height},
                    (Rectangle){o->x,o->y,o->width,o->height},
                    (Vector2){0,0}, 0.0f, WHITE);
            }
            cur = cur->next;
        }
    }
}

// Check collision player & obstacle, return count hits
int checkCollision(float x, float y, float w, float h) {
    int hits = 0;
    float marginX = w * 0.25f;
    float marginY = h * 0.10f;
    Rectangle player = {
        x + marginX,
        y + marginY,
        w * 0.50f,
        h * 0.80f
    };


    for (int i = 0; i < MAX_LANES; i++) {
        if (!lanes[i].obstacles) continue;
        
        DLNode *cur = lanes[i].obstacles->head;
        while (cur) {
            ObstacleData *o = cur->data;
            if (o && !o->hasCollided && CheckCollisionRecs(player, o->collisionBox)) {
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
        if (lanes[i].obstacles) {
            dl_destroy(lanes[i].obstacles, free);
            lanes[i].obstacles = NULL;
        }
    }
    // Jangan unload textures di sini, biarkan di unloadRintanganTextures()
}