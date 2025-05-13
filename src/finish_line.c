#include "../include/finish_line.h"
#include <raylib.h>
#include <stdlib.h>
#include "../include/config.h"

// Struktur node linked list sudah dideklarasikan di finish_line.h
static FinishTile *finishLineHead = NULL;

// Inisialisasi linked list garis finish
void InitFinishLine(void) {
    const int squareSize = 20;
    const int numSquares = SCREEN_WIDTH / squareSize;

    FinishTile *last = NULL;

    for (int i = 0; i < numSquares; i++) {
        for (int j = 0; j < 2; j++) {
            FinishTile *tile = (FinishTile *)malloc(sizeof(FinishTile));
            tile->x = i * squareSize;
            tile->y = FINISH_LINE_Y + (j * squareSize);
            tile->color = ((i + j) % 2 == 0) ? BLACK : WHITE;
            tile->next = NULL;

            if (finishLineHead == NULL) {
                finishLineHead = tile;
            } else {
                last->next = tile;
            }
            last = tile;
        }
    }
}

void DrawFinishLine(void) {
    FinishTile *current = finishLineHead;
    while (current != NULL) {
        DrawRectangle(current->x, current->y, 20, 20, current->color);
        current = current->next;
    }

    // Garis batas atas dan bawah finish line
    DrawRectangle(0, FINISH_LINE_Y - 2, SCREEN_WIDTH, 2, RED);
    DrawRectangle(0, FINISH_LINE_Y + 40, SCREEN_WIDTH, 2, RED);

    // Gambar tulisan "FINISH" di atas garis finish
    int fontSize = 40;
    int textWidth = MeasureText("FINISH", fontSize);
    int textX = (SCREEN_WIDTH - textWidth) / 2;
    int textY = FINISH_LINE_Y - 50;  // Di atas garis finish

    DrawText("FINISH", textX, textY, fontSize, RED);
}

// Periksa apakah mobil melewati garis finish
bool CheckFinishLineCollision(Car *car) {
    return (car->y + (car->height / 2) <= FINISH_LINE_Y + FINISH_LINE_HEIGHT);
}

// Bebaskan memori linked list
void FreeFinishLine(void) {
    FinishTile *current = finishLineHead;
    while (current != NULL) {
        FinishTile *temp = current;
        current = current->next;
        free(temp);
    }
    finishLineHead = NULL;
}
