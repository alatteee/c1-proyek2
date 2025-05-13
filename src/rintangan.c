#include "../include/rintangan.h"
#include "../include/skor.h"
#include "../include/config.h"
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
#define MIN_OBSTACLE_DISTANCE 600   // Jarak minimum antar obstacle secara vertikal
#define MIN_SPAWN_DELAY 1.0f        // Waktu minimal untuk spawn obstacle baru (dalam detik)
#define MAX_SPAWN_DELAY 3.0f        // Waktu maksimal untuk spawn obstacle baru (dalam detik)
#define MAX_OBSTACLES_PER_LANE 5    // Jumlah maksimum obstacle per lane

// Array untuk menyimpan textures untuk obstacle
#define NUM_OBSTACLE_TYPES 6 // Disesuaikan dengan jumlah file gambar di folder resource/obstacle
Texture2D obstacleTextures[NUM_OBSTACLE_TYPES];
char *obstacleFilenames[NUM_OBSTACLE_TYPES] = {
    "resources/obstacle/bebatuan.png",   // 0 - bebatuan
    "resources/obstacle/bus.png",        // 1 - bus
    "resources/obstacle/luxury.png",     // 2 - mobil mewah
    "resources/obstacle/mobil1.png",     // 3 - mobil biasa
    "resources/obstacle/mobil2.png",     // 4 - mobil lainnya
    "resources/obstacle/truk-sampah.png" // 5 - truk sampah
};

// Struktur untuk menyimpan informasi obstacle
typedef struct {
    float offsetXPercent; // Offset X untuk collision box (persentase dari lebar)
    float offsetYPercent; // Offset Y untuk collision box (persentase dari tinggi)
    float widthPercent;   // Lebar collision box sebagai persentase dari lebar gambar
    float heightPercent;  // Tinggi collision box sebagai persentase dari tinggi gambar
    float sizeScale;      // Faktor skala ukuran relatif terhadap ukuran standar
} ObstacleSpec;

// Definisi spec untuk setiap jenis obstacle dengan nilai yang lebih sesuai dengan bentuk visual
ObstacleSpec obstacleSpecs[NUM_OBSTACLE_TYPES] = {
    // Format: {offsetX, offsetY, widthPercent, heightPercent, sizeScale}
    {0.25, 0.20, 0.50, 0.60, 0.30}, // bebatuan - sesuaikan sedikit
    {0.30, 0.08, 0.40, 0.85, 0.80}, // bus kuning - kurangi lebar dan tinggi
    {0.30, 0.15, 0.40, 0.70, 0.55}, // luxury - kurangi lebar lebih banyak
    {0.30, 0.15, 0.40, 0.70, 0.55}, // mobil1 - kurangi lebar lebih banyak
    {0.30, 0.15, 0.40, 0.70, 0.55}, // mobil2 - kurangi lebar lebih banyak
    {0.30, 0.15, 0.40, 0.70, 0.80}  // truk-sampah hijau - kurangi lebar lebih banyak
};

// Fungsi untuk toggle collision box visibility
void toggleCollisionBoxVisibility() {
    showCollisionBoxes = !showCollisionBoxes;
    printf("Debug visualization: %s\n", showCollisionBoxes ? "ON" : "OFF");
}

// Fungsi untuk memuat texture rintangan
void loadRintanganTextures() {
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        obstacleTextures[i] = LoadTexture(obstacleFilenames[i]);
        
        // Log jika texture berhasil dimuat
        if (obstacleTextures[i].id > 0) {
            printf("Texture %d loaded successfully: %dx%d\n",
                i, obstacleTextures[i].width, obstacleTextures[i].height);
        } else {
            printf("Failed to load texture %d: %s\n", i, obstacleFilenames[i]);
        }
    }
}

// Fungsi untuk melepaskan texture rintangan
void unloadRintanganTextures() {
    for (int i = 0; i < NUM_OBSTACLE_TYPES; i++) {
        UnloadTexture(obstacleTextures[i]);
    }
    printf("All obstacle textures unloaded\n");
}

// Fungsi untuk membuat node obstacle baru
ObstacleNode* createObstacleNode(int laneIndex) {
    ObstacleNode* newNode = (ObstacleNode*)malloc(sizeof(ObstacleNode));
    if (newNode == NULL) {
        printf("Error: Failed to allocate memory for obstacle node\n");
        return NULL;
    }
    
    // Pilih tipe obstacle secara acak
    int type = rand() % NUM_OBSTACLE_TYPES;
    
    // Tentukan ukuran maksimal yang bisa muat di jalur
    float laneWidth = SCREEN_WIDTH / MAX_LANES;
    float maxObstacleWidth = laneWidth * 0.7f; // 70% dari lebar jalur
    
    // Hitung skala berdasarkan ukuran asli gambar dan faktor skala relatif
    float baseScale = maxObstacleWidth / obstacleTextures[type].width;
    float finalScale = baseScale * obstacleSpecs[type].sizeScale;
    
    // Gunakan ukuran asli gambar dikali dengan skala
    float obstacleWidth = obstacleTextures[type].width * finalScale;
    float obstacleHeight = obstacleTextures[type].height * finalScale;
    
    // Posisikan di tengah jalur
    float laneCenter = laneIndex * laneWidth + laneWidth / 2;
    float obstacleX = laneCenter - obstacleWidth / 2;
    
    // Posisikan obstacle di atas layar dengan posisi acak
    float obstacleY = -obstacleHeight - (rand() % 300);
    
    // Pastikan obstacle tidak terlalu dekat dengan obstacle terakhir di jalur
    if (lanes[laneIndex].tail != NULL) {
        float lastObstacleY = lanes[laneIndex].tail->data.y;
        if (obstacleY > lastObstacleY - MIN_OBSTACLE_DISTANCE) {
            obstacleY = lastObstacleY - MIN_OBSTACLE_DISTANCE - (rand() % 200);
        }
    }
    
    // Buat collision box yang lebih presisi
    float collisionX = obstacleX + (obstacleWidth * obstacleSpecs[type].offsetXPercent);
    float collisionY = obstacleY + (obstacleHeight * obstacleSpecs[type].offsetYPercent);
    float collisionWidth = obstacleWidth * obstacleSpecs[type].widthPercent;
    float collisionHeight = obstacleHeight * obstacleSpecs[type].heightPercent;
    
    // Isi data obstacle
    newNode->data.x = obstacleX;
    newNode->data.y = obstacleY;
    newNode->data.width = obstacleWidth;
    newNode->data.height = obstacleHeight;
    newNode->data.type = type;
    newNode->data.hasPassed = false;
    newNode->data.hasCollided = false;
    newNode->data.texture = obstacleTextures[type];
    newNode->data.collisionBox = (Rectangle){
        collisionX,
        collisionY,
        collisionWidth,
        collisionHeight
    };
    
    newNode->prev = NULL;
    newNode->next = NULL;
    
    return newNode;
}

// Fungsi untuk menambahkan obstacle ke lane
void addObstacleToLane(int laneIndex) {
    // Jangan tambahkan obstacle jika sudah mencapai batas
    if (lanes[laneIndex].obstacleCount >= MAX_OBSTACLES_PER_LANE) {
        return;
    }
    
    ObstacleNode* newNode = createObstacleNode(laneIndex);
    if (newNode == NULL) return;
    
    // Tambahkan ke linked list
    if (lanes[laneIndex].head == NULL) {
        // List kosong
        lanes[laneIndex].head = newNode;
        lanes[laneIndex].tail = newNode;
    } else {
        // Tambahkan di belakang
        newNode->prev = lanes[laneIndex].tail;
        lanes[laneIndex].tail->next = newNode;
        lanes[laneIndex].tail = newNode;
    }
    
    lanes[laneIndex].obstacleCount++;
}

// Fungsi untuk menghapus obstacle dari lane
void removeObstacleFromLane(int laneIndex, ObstacleNode* node) {
    if (node == NULL) return;
    
    // Update linked list
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // Node adalah head
        lanes[laneIndex].head = node->next;
    }
    
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        // Node adalah tail
        lanes[laneIndex].tail = node->prev;
    }
    
    free(node);
    lanes[laneIndex].obstacleCount--;
}

// Fungsi untuk inisialisasi sistem rintangan
void initRintangan() {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    // Load textures
    static bool texturesLoaded = false;
    if (!texturesLoaded) {
        loadRintanganTextures();
        texturesLoaded = true;
    }
    
    // Inisialisasi lanes
    for (int i = 0; i < MAX_LANES; i++) {
        lanes[i].head = NULL;
        lanes[i].tail = NULL;
        lanes[i].obstacleCount = 0;
        lanes[i].nextSpawnTime = (float)(rand() % 100) / 100.0f; // Random initial spawn time
        
        // Tambahkan obstacle pertama untuk setiap lane dengan posisi eschelon
        addObstacleToLane(i);
        if (lanes[i].head != NULL) {
            lanes[i].head->data.y = -300 - i * 400; // Stagger initial positions
        }
    }
}

// Fungsi untuk membersihkan semua obstacle
void freeRintangan() {
    for (int i = 0; i < MAX_LANES; i++) {
        ObstacleNode* current = lanes[i].head;
        while (current != NULL) {
            ObstacleNode* next = current->next;
            free(current);
            current = next;
        }
        lanes[i].head = NULL;
        lanes[i].tail = NULL;
        lanes[i].obstacleCount = 0;
    }
}

// Fungsi untuk memperbarui obstacle
void updateRintangan(Skor *skor, int obstacleSpeed) {
    float deltaTime = GetFrameTime();
    
    // Update spawn timers untuk setiap lane
    for (int lane = 0; lane < MAX_LANES; lane++) {
        lanes[lane].nextSpawnTime -= deltaTime;
        
        // Jika timer habis dan jumlah obstacle belum maksimum, tambahkan obstacle baru
        if (lanes[lane].nextSpawnTime <= 0 && lanes[lane].obstacleCount < MAX_OBSTACLES_PER_LANE) {
            addObstacleToLane(lane);
            
            // Reset timer dengan variasi
            float randomDelay = MIN_SPAWN_DELAY + ((float)rand() / RAND_MAX) * (MAX_SPAWN_DELAY - MIN_SPAWN_DELAY);
            lanes[lane].nextSpawnTime = randomDelay;
        }
    }
    
    // Update posisi semua obstacle
    for (int lane = 0; lane < MAX_LANES; lane++) {
        ObstacleNode* current = lanes[lane].head;
        while (current != NULL) {
            // Ambil pointer ke node berikutnya sebelum kita mungkin menghapus current
            ObstacleNode* next = current->next;
            
            // Gerakkan obstacle ke bawah
            float moveAmount = obstacleSpeed;
            current->data.y += moveAmount;
            
            // Update collision box - perbarui semua properti untuk memastikan akurasi
            current->data.collisionBox.x = current->data.x + (current->data.width * obstacleSpecs[current->data.type].offsetXPercent);
            current->data.collisionBox.y = current->data.y + (current->data.height * obstacleSpecs[current->data.type].offsetYPercent);
            current->data.collisionBox.width = current->data.width * obstacleSpecs[current->data.type].widthPercent;
            current->data.collisionBox.height = current->data.height * obstacleSpecs[current->data.type].heightPercent;
            
            // Jika obstacle telah melewati layar dan belum dihitung
            if (current->data.y > SCREEN_HEIGHT && !current->data.hasPassed) {
                current->data.hasPassed = true;
                skor->nilai += 10;
            }
            
            // Hapus obstacle jika sudah keluar dari layar
            if (current->data.y > SCREEN_HEIGHT + current->data.height) {
                removeObstacleFromLane(lane, current);
            }
            
            current = next;
        }
    }
}

// Fungsi untuk menggambar semua obstacle
void drawRintangan() {
    for (int lane = 0; lane < MAX_LANES; lane++) {
        ObstacleNode* current = lanes[lane].head;
        while (current != NULL) {
            if (current->data.y >= -current->data.height) { // Hanya gambar jika terlihat
                // Gambar texture sesuai ukuran yang telah dihitung
                DrawTexturePro(
                    current->data.texture,
                    (Rectangle){0, 0, current->data.texture.width, current->data.texture.height},
                    (Rectangle){
                        current->data.x,
                        current->data.y,
                        current->data.width,
                        current->data.height
                    },
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            }
            current = current->next;
        }
    }
}

// Fungsi untuk menggambar collision box untuk debugging
void drawCollisionBoxes(bool drawPlayerBox, float x, float y, float width, float height) {
    if (!showCollisionBoxes) return;
    
    // Gambar collision box untuk player
    if (drawPlayerBox) {
        float playerMarginX = width * 0.25;
        float playerMarginY = height * 0.10;
        
        Rectangle playerRec = {
            x + playerMarginX,
            y + playerMarginY,
            width * 0.50,
            height * 0.80
        };
        
        DrawRectangleLines(playerRec.x, playerRec.y, playerRec.width, playerRec.height, BLUE);
    }
    
    // Gambar collision box untuk semua obstacle
    for (int lane = 0; lane < MAX_LANES; lane++) {
        ObstacleNode* current = lanes[lane].head;
        while (current != NULL) {
            if (current->data.y >= -current->data.height) {
                // Gunakan collision box yang sudah diperbarui di updateRintangan
                DrawRectangleLines(
                    current->data.collisionBox.x,
                    current->data.collisionBox.y,
                    current->data.collisionBox.width,
                    current->data.collisionBox.height,
                    RED);
            }
            current = current->next;
        }
    }
}

// Fungsi untuk memeriksa tabrakan dengan obstacle
int checkCollision(float x, float y, float width, float height) {
    int collisionCount = 0;
    
    // Collision box untuk player - sesuaikan ukuran agar lebih akurat
    float playerMarginX = width * 0.25;
    float playerMarginY = height * 0.10;
    
    Rectangle playerRec = {
        x + playerMarginX,
        y + playerMarginY,
        width * 0.50,
        height * 0.80
    };
    
    // Periksa collision dengan semua obstacle
    for (int lane = 0; lane < MAX_LANES; lane++) {
        ObstacleNode* current = lanes[lane].head;
        while (current != NULL) {
            if (current->data.y >= 0 && !current->data.hasCollided) {
                // Gunakan collision box yang sudah diperbarui di updateRintangan
                if (CheckCollisionRecs(playerRec, current->data.collisionBox)) {
                    current->data.hasCollided = true;
                    collisionCount++;
                }
            }
            current = current->next;
        }
    }
    
    return collisionCount;
}