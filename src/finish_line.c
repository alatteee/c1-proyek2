#include "../include/finish_line.h"  // Contains FINISH_LINE_Y and FINISH_LINE_HEIGHT
#include <raylib.h>
#include "../include/config.h"

// Fungsi untuk menggambar garis finish dengan pola papan catur
void DrawFinishLine(void) {
    const int squareSize = 20;  // Ukuran setiap kotak pada pola papan catur
    const int numSquares = SCREEN_WIDTH / squareSize; // Jumlah kotak horizontal

    // Loop untuk menggambar pola papan catur
    for (int i = 0; i < numSquares; i++) {
        for (int j = 0; j < 2; j++) {  // 2 baris kotak untuk garis finish
            // Tentukan warna kotak (hitam atau putih berdasarkan pola papan catur)
            Color squareColor = ((i + j) % 2 == 0) ? BLACK : WHITE;

            // Hitung posisi X dan Y untuk setiap kotak
            int x = i * squareSize;
            int y = FINISH_LINE_Y + (j * squareSize);

            // Gambar kotak dengan warna yang telah ditentukan
            DrawRectangle(x, y, squareSize, squareSize, squareColor);
        }
    }

    // Tambahkan batas atas dan bawah untuk membuat garis finish lebih menonjol
    DrawRectangle(0, FINISH_LINE_Y - 2, SCREEN_WIDTH, 2, RED);           // Batas atas
    DrawRectangle(0, FINISH_LINE_Y + (2 * squareSize), SCREEN_WIDTH, 2, RED); // Batas bawah
}

// Fungsi untuk memeriksa apakah mobil telah melewati garis finish
bool CheckFinishLineCollision(Car *car) {
    // Cek apakah posisi Y mobil telah melewati atau mencapai garis finish
    if (car->y <= FINISH_LINE_Y + FINISH_LINE_HEIGHT) {
        return true; // Pemain mencapai garis finish
    }
    return false; // Pemain belum mencapai garis finish
}