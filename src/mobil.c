/* ----------------------------------------------------------------------------- */
/* File        : mobil.c                                                         */
/* Deskripsi   : File implementasi untuk mengelola mobil dalam game. Berisi      */
/*              fungsi-fungsi untuk menginisialisasi, merender, menggerakkan,    */
/*              dan menangani logika mobil, termasuk invulnerability dan deteksi*/
/*              tabrakan.                                                       */
/* ----------------------------------------------------------------------------- */

#include "../include/mobil.h"  // File header untuk mobil
#include "../include/config.h" // File konfigurasi game
#include "../include/lives.h"  // File header untuk sistem nyawa
#include <raylib.h>            // Library Raylib untuk grafik dan utilitas

// Fungsi untuk menginisialisasi mobil
void initCar(Car *car, float x, float y, float width, float height, int speed) {
  car->x = x;                     // Set posisi X mobil
  car->y = y;                     // Set posisi Y mobil
  car->width = width;             // Set lebar mobil
  car->height = height;           // Set tinggi mobil
  car->speed = speed;             // Set kecepatan mobil
  car->rect = (Rectangle){car->x, car->y, car->width, car->height}; // Set persegi panjang untuk collision detection
  car->isInvulnerable = false;    // Set status invulnerable ke false
  car->invulnerabilityTimer = 0.0f; // Set timer invulnerability ke 0
}

// Fungsi untuk merender mobil dengan desain top-down seperti mobil sport kuning
void renderCar(Car *car) {
  // Warna-warna yang akan digunakan
  Color bodyColor = ORANGE;      // Orange-kuning untuk badan mobil
  Color windowColor = BLACK;     // Hitam untuk kaca mobil
  Color highlightColor = YELLOW; // Kuning emas untuk highlight
  Color headlightColor = BLUE;   // Biru untuk lampu depan
  Color tailLightColor = RED;    // Merah untuk lampu belakang
  Color detailColor = DARKGRAY;  // Abu-abu untuk detail

  float carWidth = car->width;   // Lebar mobil
  float carHeight = car->height; // Tinggi mobil
  float carX = car->x;           // Posisi X mobil
  float carY = car->y;           // Posisi Y mobil

  // Bayangan mobil 
  DrawRectangle(carX + 3, carY + 3, carWidth, carHeight, Fade(BLACK, 0.2f));

  // Badan mobil utama (bentuk oval)
  DrawRectangle(carX + carWidth * 0.2f, carY + carHeight * 0.15f, carWidth * 0.6f, carHeight * 0.7f, bodyColor);  // Badan tengah
  DrawRectangle(carX + carWidth * 0.3f, carY, carWidth * 0.4f, carHeight * 0.15f, bodyColor);                     // Bagian depan
  DrawRectangle(carX + carWidth * 0.3f, carY + carHeight * 0.85f, carWidth * 0.4f, carHeight * 0.15f, bodyColor); // Bagian belakang

  // Garis highlight sepanjang mobil
  DrawRectangle(carX + carWidth * 0.3f, carY + carHeight * 0.1f, carWidth * 0.05f, carHeight * 0.8f, highlightColor);  // Highlight kiri
  DrawRectangle(carX + carWidth * 0.65f, carY + carHeight * 0.1f, carWidth * 0.05f, carHeight * 0.8f, highlightColor); // Highlight kanan

  // Kaca depan (bentuk trapesium)
  DrawRectangle(carX + carWidth * 0.35f, carY + carHeight * 0.2f, carWidth * 0.3f, carHeight * 0.15f, windowColor);  // Kaca depan
  DrawRectangle(carX + carWidth * 0.35f, carY + carHeight * 0.65f, carWidth * 0.3f, carHeight * 0.15f, windowColor); // Kaca belakang

  // Spoiler kecil di belakang
  DrawRectangle(carX + carWidth * 0.35f, carY + carHeight * 0.9f, carWidth * 0.3f, carHeight * 0.05f, detailColor);

  // Lampu depan (kiri dan kanan)
  DrawRectangle(carX + carWidth * 0.3f, carY + carHeight * 0.05f, carWidth * 0.1f, carHeight * 0.05f, headlightColor); // Lampu depan kiri
  DrawRectangle(carX + carWidth * 0.6f, carY + carHeight * 0.05f, carWidth * 0.1f, carHeight * 0.05f, headlightColor); // Lampu depan kanan

  // Lampu belakang (kiri dan kanan)
  DrawRectangle(carX + carWidth * 0.3f, carY + carHeight * 0.9f, carWidth * 0.1f, carHeight * 0.05f, tailLightColor); // Lampu belakang kiri
  DrawRectangle(carX + carWidth * 0.6f, carY + carHeight * 0.9f, carWidth * 0.1f, carHeight * 0.05f, tailLightColor); // Lampu belakang kanan

  // Detail tengah mobil (kokpit atau garis tengah)
  DrawRectangle(carX + carWidth * 0.48f, carY + carHeight * 0.2f, carWidth * 0.04f, carHeight * 0.6f, detailColor);

  // Detail roda (dalam tampilan top-down, roda hanya terlihat sedikit di sisi)
  DrawRectangle(carX + carWidth * 0.15f, carY + carHeight * 0.25f, carWidth * 0.07f, carHeight * 0.15f, DARKGRAY); // Roda depan kiri
  DrawRectangle(carX + carWidth * 0.78f, carY + carHeight * 0.25f, carWidth * 0.07f, carHeight * 0.15f, DARKGRAY); // Roda depan kanan
  DrawRectangle(carX + carWidth * 0.15f, carY + carHeight * 0.6f, carWidth * 0.07f, carHeight * 0.15f, DARKGRAY);  // Roda belakang kiri
  DrawRectangle(carX + carWidth * 0.78f, carY + carHeight * 0.6f, carWidth * 0.07f, carHeight * 0.15f, DARKGRAY);  // Roda belakang kanan
}

// Fungsi untuk menangani input gerakan mobil
void handleCarInput(Car *car) {
  if (IsKeyDown(KEY_LEFT))
      car->x -= car->speed; // Gerakkan mobil ke kiri
  if (IsKeyDown(KEY_RIGHT)) 
      car->x += car->speed; // Gerakkan mobil ke kanan
  if (IsKeyDown(KEY_UP)) 
      car->y -= car->speed; // Gerakkan mobil ke atas
  if (IsKeyDown(KEY_DOWN)) 
      car->y += car->speed; // Gerakkan mobil ke bawah

  // Batasi mobil agar tidak keluar dari layar
  if (car->x < 0) car->x = 0;
  if (car->x + car->width > SCREEN_WIDTH) car->x = SCREEN_WIDTH - car->width;
  if (car->y < 0) car->y = 0;
  if (car->y + car->height > SCREEN_HEIGHT) car->y = SCREEN_HEIGHT - car->height;

  // Update persegi panjang mobil untuk collision detection
  car->rect = (Rectangle){car->x, car->y, car->width, car->height};
}

// Fungsi untuk mereset posisi mobil ke posisi awal
void resetCarPosition(Car *car) {
  car->x = MIDDLE_LANE_X; // Set posisi X ke tengah layar
  car->y = SCREEN_HEIGHT - PLAYER_CAR_HEIGHT - 10.0f; // Set posisi Y ke bagian bawah layar
  car->rect = (Rectangle){car->x, car->y, car->width, car->height}; // Update persegi panjang mobil
}

// Fungsi untuk memperbarui status invulnerability mobil
void updateCarInvulnerability(Car *car, float deltaTime) {
  if (car->isInvulnerable) {
      car->invulnerabilityTimer += deltaTime; // Tambahkan waktu ke timer
      if (car->invulnerabilityTimer >= INVULNERABILITY_DURATION) {
          car->isInvulnerable = false; // Nonaktifkan invulnerability setelah durasi selesai
          car->invulnerabilityTimer = 0.0f; // Reset timer
      }
  }
}

// Fungsi untuk memeriksa tabrakan antara mobil dan rintangan
bool checkCarCollision(Car *car, Rectangle obstacle) {
  // Debugging: Tampilkan posisi dan ukuran mobil serta rintangan
  TraceLog(LOG_INFO, "Mobil: x=%.2f, y=%.2f, width=%.2f, height=%.2f", car->rect.x, car->rect.y, car->rect.width, car->rect.height);
  TraceLog(LOG_INFO, "Rintangan: x=%.2f, y=%.2f, width=%.2f, height=%.2f", obstacle.x, obstacle.y, obstacle.width, obstacle.height);

  // Periksa tabrakan jika mobil tidak dalam keadaan invulnerable
  if (!car->isInvulnerable && CheckCollisionRecs(car->rect, obstacle)) {
      TraceLog(LOG_INFO, "Tabrakan terdeteksi!");
      car->isInvulnerable = true; // Aktifkan invulnerability
      car->invulnerabilityTimer = 0.0f; // Reset timer
      return true; // Tabrakan terjadi
  }
  return false; // Tidak ada tabrakan
}
