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

// Fungsi untuk menggambar mobil dengan desain top-down seperti gambar sport car kuning
void renderCar(SDL_Renderer *renderer, Car *car)
{
    // Warna-warna yang akan digunakan
    SDL_Color bodyColor = {255, 165, 0, 255};         // Orange-kuning untuk badan
    SDL_Color windowColor = {0, 0, 0, 255};           // Hitam untuk kaca
    SDL_Color highlightColor = {255, 215, 0, 255};    // Kuning emas untuk highlight
    SDL_Color headlightColor = {255, 255, 224, 255};  // Kuning pucat untuk lampu depan
    SDL_Color tailLightColor = {255, 0, 0, 255};      // Merah untuk lampu belakang
    SDL_Color detailColor = {100, 100, 100, 255};     // Abu-abu untuk detail
    
    float carWidth = car->rect.w;
    float carHeight = car->rect.h;
    float carX = car->rect.x;
    float carY = car->rect.y;
    
    // Bayangan mobil (opsional)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_FRect shadow = {carX + 3.0f, carY + 3.0f, carWidth, carHeight};
    SDL_RenderFillRect(renderer, &shadow);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // Badan mobil utama (bentuk oval)
    SDL_SetRenderDrawColor(renderer, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    // Pada SDL kita perlu menggambar bentuk oval dengan beberapa persegi panjang
    
    // Bagian tengah badan (bagian terlebar)
    SDL_FRect bodyMiddle = {carX + carWidth * 0.2f, carY + carHeight * 0.15f, carWidth * 0.6f, carHeight * 0.7f};
    SDL_RenderFillRect(renderer, &bodyMiddle);
    
    // Bagian depan badan (agak meruncing)
    SDL_FRect bodyFront = {carX + carWidth * 0.3f, carY, carWidth * 0.4f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &bodyFront);
    
    // Bagian belakang badan (agak meruncing)
    SDL_FRect bodyRear = {carX + carWidth * 0.3f, carY + carHeight * 0.85f, carWidth * 0.4f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &bodyRear);
    
    // Garis highlight sepanjang mobil
    SDL_SetRenderDrawColor(renderer, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
    SDL_FRect leftHighlight = {carX + carWidth * 0.3f, carY + carHeight * 0.1f, carWidth * 0.05f, carHeight * 0.8f};
    SDL_RenderFillRect(renderer, &leftHighlight);
    
    SDL_FRect rightHighlight = {carX + carWidth * 0.65f, carY + carHeight * 0.1f, carWidth * 0.05f, carHeight * 0.8f};
    SDL_RenderFillRect(renderer, &rightHighlight);
    
    // Kaca depan (bentuk trapesium)
    SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
    SDL_FRect frontWindow = {carX + carWidth * 0.35f, carY + carHeight * 0.2f, carWidth * 0.3f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &frontWindow);
    
    // Kaca belakang (bentuk trapesium)
    SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
    SDL_FRect rearWindow = {carX + carWidth * 0.35f, carY + carHeight * 0.65f, carWidth * 0.3f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &rearWindow);
    
    // Spoiler kecil di belakang
    SDL_SetRenderDrawColor(renderer, detailColor.r, detailColor.g, detailColor.b, detailColor.a);
    SDL_FRect spoiler = {carX + carWidth * 0.35f, carY + carHeight * 0.9f, carWidth * 0.3f, carHeight * 0.05f};
    SDL_RenderFillRect(renderer, &spoiler);
    
    // Lampu depan (kiri dan kanan)
    SDL_SetRenderDrawColor(renderer, headlightColor.r, headlightColor.g, headlightColor.b, headlightColor.a);
    SDL_FRect leftHeadlight = {carX + carWidth * 0.3f, carY + carHeight * 0.05f, carWidth * 0.1f, carHeight * 0.05f};
    SDL_RenderFillRect(renderer, &leftHeadlight);
    
    SDL_FRect rightHeadlight = {carX + carWidth * 0.6f, carY + carHeight * 0.05f, carWidth * 0.1f, carHeight * 0.05f};
    SDL_RenderFillRect(renderer, &rightHeadlight);
    
    // Lampu belakang (kiri dan kanan)
    SDL_SetRenderDrawColor(renderer, tailLightColor.r, tailLightColor.g, tailLightColor.b, tailLightColor.a);
    SDL_FRect leftTaillight = {carX + carWidth * 0.3f, carY + carHeight * 0.9f, carWidth * 0.1f, carHeight * 0.05f};
    SDL_RenderFillRect(renderer, &leftTaillight);
    
    SDL_FRect rightTaillight = {carX + carWidth * 0.6f, carY + carHeight * 0.9f, carWidth * 0.1f, carHeight * 0.05f};
    SDL_RenderFillRect(renderer, &rightTaillight);
    
    // Detail tengah mobil (kokpit atau garis tengah)
    SDL_SetRenderDrawColor(renderer, detailColor.r, detailColor.g, detailColor.b, detailColor.a);
    SDL_FRect centerLine = {carX + carWidth * 0.48f, carY + carHeight * 0.2f, carWidth * 0.04f, carHeight * 0.6f};
    SDL_RenderFillRect(renderer, &centerLine);
    
    // Detail roda (dalam tampilan top-down, roda hanya terlihat sedikit di sisi)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Warna hitam gelap untuk ban
    
    // Roda depan kiri
    SDL_FRect frontLeftWheel = {carX + carWidth * 0.15f, carY + carHeight * 0.25f, carWidth * 0.07f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &frontLeftWheel);
    
    // Roda depan kanan
    SDL_FRect frontRightWheel = {carX + carWidth * 0.78f, carY + carHeight * 0.25f, carWidth * 0.07f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &frontRightWheel);
    
    // Roda belakang kiri
    SDL_FRect rearLeftWheel = {carX + carWidth * 0.15f, carY + carHeight * 0.6f, carWidth * 0.07f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &rearLeftWheel);
    
    // Roda belakang kanan
    SDL_FRect rearRightWheel = {carX + carWidth * 0.78f, carY + carHeight * 0.6f, carWidth * 0.07f, carHeight * 0.15f};
    SDL_RenderFillRect(renderer, &rearRightWheel);
    
    // menambahkan efek highlight di badan mobil
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 30);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_FRect bodyHighlight = {carX + carWidth * 0.4f, carY + carHeight * 0.3f, carWidth * 0.2f, carHeight * 0.4f};
    SDL_RenderFillRect(renderer, &bodyHighlight);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}