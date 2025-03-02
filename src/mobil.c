#include "../include/mobil.h"

// Fungsi untuk inisialisasi mobil
void initCar(Car *car, float x, float y, float width, float height, int speed)
{
  car->x = x;
  car->y = y;
  car->width = width;
  car->height = height;
  car->speed = speed;
  car->rect.x = x;
  car->rect.y = y;
  car->rect.w = width;
  car->rect.h = height;
}

// Fungsi untuk menggerakkan mobil ke kiri
void moveLeft(Car *car)
{
  if (car->x > 0)
  {
    car->x -= car->speed;
    car->rect.x = car->x; // Pastikan rect.x diperbarui
  }
}

// Fungsi untuk menggerakkan mobil ke kanan
void moveRight(Car *car, int screenWidth)
{
  if (car->x + car->width < screenWidth)
  {
    car->x += car->speed; // Menggunakan kecepatan yang benar
    car->rect.x = car->x; // Pastikan rect.x diperbarui
  }
}

// Fungsi untuk menggambar mobil dengan kotak-kotak yang lebih modular
void renderCar(SDL_Renderer *renderer, Car *car)
{
  // Gambar tubuh mobil (kotak besar di tengah)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);                                         // Merah untuk tubuh mobil
  SDL_FRect body1 = {car->rect.x + 10.0f, car->rect.y + 60.0f, car->rect.w - 20.0f, 40.0f}; // Kotak besar tengah
  SDL_RenderFillRect(renderer, &body1);

  // Gambar atap mobil (kotak kecil di atas tubuh mobil)
  SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);                                      // Warna oranye untuk atap
  SDL_FRect roof = {car->rect.x + 15.0f, car->rect.y + 30.0f, car->rect.w - 30.0f, 30.0f}; // Posisi dan ukuran atap
  SDL_RenderFillRect(renderer, &roof);                                                     // Bagian atap mobil

  // Gambar roda mobil (kotak-kotak kecil untuk roda)
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);                                                        // Hijau untuk roda
  SDL_FRect wheel1 = {car->rect.x + 10.0f, car->rect.y + car->rect.h - 20.0f, 30.0f, 20.0f};               // Roda kiri
  SDL_FRect wheel2 = {car->rect.x + car->rect.w - 40.0f, car->rect.y + car->rect.h - 20.0f, 30.0f, 20.0f}; // Roda kanan
  SDL_RenderFillRect(renderer, &wheel1);
  SDL_RenderFillRect(renderer, &wheel2);
}
