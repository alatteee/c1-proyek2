#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include "config.h"
#include "mobil.h"  
#include <stdbool.h>

// Definisi posisi Y garis finish di layar (50 pixel dari atas)
#define FINISH_LINE_Y 50        
// Definisi tinggi garis finish (10 pixel)
#define FINISH_LINE_HEIGHT 10   

// Deklarasi fungsi untuk menggambar garis finish di layar
void DrawFinishLine(void);
// Deklarasi fungsi untuk memeriksa apakah mobil telah melewati garis finish (tabrakan dengan garis finish)
bool CheckFinishLineCollision(Car *car);

#endif // FINISH_LINE_H