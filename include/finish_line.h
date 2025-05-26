#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include "config.h"
#include "mobil.h"  
#include "single_linked_list.h"
#include <stdbool.h>

// Definisi posisi Y garis finish di layar (50 pixel dari atas)
#define FINISH_LINE_Y 50        
// Definisi tinggi garis finish (10 pixel)
#define FINISH_LINE_HEIGHT 10   

typedef struct {
    int x, y;
    int width, height;
    Color color;
} FinishLineSegment;

// Deklarasi fungsi untuk menggambar garis finish di layar
void DrawFinishLine(void);
// Deklarasi fungsi untuk memeriksa apakah mobil telah melewati garis finish
bool CheckFinishLineCollision(Car *car);
// Fungsi untuk membuat segmen finish line
List* createFinishLineSegments(void);
FinishLineSegment* createFinishLineSegment(int x, int y, int width, int height, Color color);
void freeFinishLineSegment(void* data);
void drawFinishLineSegment(void* data);

#endif // FINISH_LINE_H