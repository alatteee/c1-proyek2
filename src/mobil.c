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

// Fungsi untuk menggambar mobil dengan desain yang lebih baik dan realistis
void renderCar(SDL_Renderer *renderer, Car *car)
{
    // Warna-warna yang akan digunakan
    SDL_Color bodyColor = {30, 144, 255, 255};       // Biru laut untuk badan
    SDL_Color windowColor = {135, 206, 250, 255};    // Biru muda untuk kaca
    SDL_Color wheelColor = {40, 40, 40, 255};        // Hitam gelap untuk ban
    SDL_Color wheelRimColor = {192, 192, 192, 255};  // Silver untuk velg
    SDL_Color headlightColor = {255, 255, 224, 255}; // Kuning pucat untuk lampu
    SDL_Color grillColor = {50, 50, 50, 255};        // Abu-abu gelap untuk grill
    
    float carWidth = car->rect.w;
    float carHeight = car->rect.h;
    float carX = car->rect.x;
    float carY = car->rect.y;
    
    // Menambahkan bayangan di bawah mobil
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_FRect shadow = {carX + 5.0f, carY + carHeight - 5.0f, carWidth - 10.0f, 10.0f};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &shadow);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // Badan mobil utama (lebih aerodinamis)
    SDL_SetRenderDrawColor(renderer, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    SDL_FRect body = {carX + 10.0f, carY + 50.0f, carWidth - 20.0f, 45.0f};
    SDL_RenderFillRect(renderer, &body);
    
    // Kap mesin (depan mobil)
    SDL_SetRenderDrawColor(renderer, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    SDL_FRect hood = {carX + 15.0f, carY + 40.0f, carWidth - 90.0f, 10.0f};
    SDL_RenderFillRect(renderer, &hood);
    
    // Bagian belakang mobil
    SDL_FRect trunk = {carX + carWidth - 75.0f, carY + 40.0f, 60.0f, 10.0f};
    SDL_RenderFillRect(renderer, &trunk);
    
    // Kabin mobil (atap dengan kaca)
    SDL_SetRenderDrawColor(renderer, bodyColor.r - 20, bodyColor.g - 20, bodyColor.b - 20, bodyColor.a);
    SDL_FRect cabin = {carX + carWidth - 85.0f, carY + 25.0f, 70.0f, 15.0f};
    SDL_RenderFillRect(renderer, &cabin);
    
    // Kaca depan
    SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
    SDL_FRect windshield = {carX + carWidth - 85.0f, carY + 25.0f, 10.0f, 15.0f};
    SDL_RenderFillRect(renderer, &windshield);
    
    // Kaca samping
    SDL_FRect sideWindow = {carX + carWidth - 75.0f, carY + 25.0f, 50.0f, 15.0f};
    SDL_RenderFillRect(renderer, &sideWindow);
    
    // Kaca belakang
    SDL_FRect rearWindow = {carX + carWidth - 25.0f, carY + 25.0f, 10.0f, 15.0f};
    SDL_RenderFillRect(renderer, &rearWindow);
    
    // Lampu depan
    SDL_SetRenderDrawColor(renderer, headlightColor.r, headlightColor.g, headlightColor.b, headlightColor.a);
    SDL_FRect headlight = {carX + 10.0f, carY + 50.0f, 5.0f, 10.0f};
    SDL_RenderFillRect(renderer, &headlight);
    
    // Lampu belakang
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Merah untuk lampu belakang
    SDL_FRect taillight = {carX + carWidth - 15.0f, carY + 50.0f, 5.0f, 10.0f};
    SDL_RenderFillRect(renderer, &taillight);
    
    // Gril depan
    SDL_SetRenderDrawColor(renderer, grillColor.r, grillColor.g, grillColor.b, grillColor.a);
    SDL_FRect grill = {carX + 15.0f, carY + 60.0f, 20.0f, 10.0f};
    SDL_RenderFillRect(renderer, &grill);
    
    // Roda-roda mobil dengan velg
    // Roda depan
    SDL_SetRenderDrawColor(renderer, wheelColor.r, wheelColor.g, wheelColor.b, wheelColor.a);
    SDL_FRect frontWheel = {carX + 25.0f, carY + carHeight - 25.0f, 30.0f, 20.0f};
    SDL_RenderFillRect(renderer, &frontWheel);
    
    // Velg roda depan
    SDL_SetRenderDrawColor(renderer, wheelRimColor.r, wheelRimColor.g, wheelRimColor.b, wheelRimColor.a);
    SDL_FRect frontWheelRim = {carX + 35.0f, carY + carHeight - 20.0f, 10.0f, 10.0f};
    SDL_RenderFillRect(renderer, &frontWheelRim);
    
    // Roda belakang
    SDL_SetRenderDrawColor(renderer, wheelColor.r, wheelColor.g, wheelColor.b, wheelColor.a);
    SDL_FRect rearWheel = {carX + carWidth - 55.0f, carY + carHeight - 25.0f, 30.0f, 20.0f};
    SDL_RenderFillRect(renderer, &rearWheel);
    
    // Velg roda belakang
    SDL_SetRenderDrawColor(renderer, wheelRimColor.r, wheelRimColor.g, wheelRimColor.b, wheelRimColor.a);
    SDL_FRect rearWheelRim = {carX + carWidth - 45.0f, carY + carHeight - 20.0f, 10.0f, 10.0f};
    SDL_RenderFillRect(renderer, &rearWheelRim);
    
    // Menambahkan efek pencahayaan (highlight) pada badan mobil untuk kesan lebih realistis
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_FRect highlight = {carX + 20.0f, carY + 55.0f, carWidth - 40.0f, 5.0f};
    SDL_RenderFillRect(renderer, &highlight);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
