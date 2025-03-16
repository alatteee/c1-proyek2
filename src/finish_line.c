// finish_line.c
#include "../include/finish_line.h"
#include <raylib.h>
#include "../include/config.h"

void DrawFinishLine() {
    const int squareSize = 20;  // Ukuran setiap kotak pada pola papan catur
    const int numSquares = SCREEN_WIDTH / squareSize;
    
    for (int i = 0; i < numSquares; i++) {
        for (int j = 0; j < 2; j++) {  // 2 baris kotak untuk garis finish
            Color squareColor = ((i + j) % 2 == 0) ? BLACK : WHITE;  // Pola papan catur
            
            int x = i * squareSize;
            int y = FINISH_LINE_Y + (j * squareSize);
            
            DrawRectangle(x, y, squareSize, squareSize, squareColor);
        }
    }
    
    // Tambahkan batas atas dan bawah untuk membuat garis finish lebih menonjol
    DrawRectangle(0, FINISH_LINE_Y - 2, SCREEN_WIDTH, 2, RED);
    DrawRectangle(0, FINISH_LINE_Y + (2 * squareSize), SCREEN_WIDTH, 2, RED);
}

bool CheckFinishLineCollision(Car *car) {
    // Cek apakah mobil telah melewati garis finish
    if (car->y <= FINISH_LINE_Y + FINISH_LINE_HEIGHT) {
        return true; // Pemain mencapai garis finish
    }
    return false; // Pemain belum mencapai garis finish
}
