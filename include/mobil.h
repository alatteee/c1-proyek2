#ifndef MOBIL_H
#define MOBIL_H

#include <raylib.h>

// Struktur untuk mobil
typedef struct
{
  float x;        // Posisi X mobil
  float y;        // Posisi Y mobil
  float width;    // Lebar mobil
  float height;   // Tinggi mobil
  Rectangle rect; // Menggunakan Rectangle Raylib untuk rendering
  int speed;      // Kecepatan mobil
} Car;

void initCar(Car *car, float x, float y, float w, float h, int speed);
void moveLeft(Car *car);
void moveRight(Car *car, int screenWidth);
void renderCar(Car *car);

#endif // MOBIL_H
