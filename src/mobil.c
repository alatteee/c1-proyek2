#include "../include/mobil.h"
#include "../include/config.h"
#include <raylib.h>

// Fungsi untuk inisialisasi mobil
void initCar(Car *car, float x, float y, float width, float height, int speed)
{
  car->x = x;
  car->y = y;
  car->width = width;
  car->height = height;
  car->speed = speed;
}

// Fungsi untuk menggambar mobil dengan desain top-down seperti gambar sport car kuning
void renderCar(Car *car)
{
  // Warna-warna yang akan digunakan
  Color bodyColor = ORANGE;      // Orange-kuning untuk badan
  Color windowColor = BLACK;     // Hitam untuk kaca
  Color highlightColor = YELLOW; // Kuning emas untuk highlight
  Color headlightColor = BLUE;   // Kuning pucat untuk lampu depan
  Color tailLightColor = RED;    // Merah untuk lampu belakang
  Color detailColor = DARKGRAY;  // Abu-abu untuk detail

  float carWidth = car->width;
  float carHeight = car->height;
  float carX = car->x;
  float carY = car->y;

  // Bayangan mobil (opsional)
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
void handleCarInput(Car *car)
{
    if (IsKeyDown(KEY_LEFT) && car->x > 0) 
        car->x -= car->speed;
    if (IsKeyDown(KEY_RIGHT) && car->x + car->width < SCREEN_WIDTH) 
        car->x += car->speed;
    if (IsKeyDown(KEY_UP) && car->y > 0) 
        car->y -= car->speed;
    if (IsKeyDown(KEY_DOWN) && car->y + car->height < SCREEN_HEIGHT) 
        car->y += car->speed;
}