#include "../include/finish_line.h"
#include <stdlib.h>

// Ukuran kotak finish
#define TILE_SIZE 20

// Callback buat gambar satu tile
static void _drawTile(void *d) {
    FinishTile *t = d;
    DrawRectangle(t->x, t->y, TILE_SIZE, TILE_SIZE, t->color);
}

// Buat dan isi list tile
List* InitFinishLine(void) {
    List *lst = buatList();
    int numCols = SCREEN_WIDTH / TILE_SIZE;
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < 2; j++) {
            FinishTile *t = malloc(sizeof *t);
            t->x     = i * TILE_SIZE;
            t->y     = FINISH_LINE_Y + j * TILE_SIZE;
            t->color = ((i + j) % 2 == 0) ? BLACK : WHITE;
            tambahData(lst, t);
        }
    }
    return lst;
}

// Gambar semua kotak, garis & teks
void DrawFinishLine(List* finishList) {
    // gambar kotak-kotak
    tampilkanList(finishList, _drawTile);

    // garis merah atas/bawah
    DrawRectangle(0, FINISH_LINE_Y - 2, SCREEN_WIDTH, 2, RED);
    DrawRectangle(0, FINISH_LINE_Y + FINISH_LINE_HEIGHT, SCREEN_WIDTH, 2, RED);

    // teks FINISH di atas
    const char *txt = "FINISH";
    int fw = MeasureText(txt, 40);
    DrawText(txt, (SCREEN_WIDTH - fw)/2, FINISH_LINE_Y - 50, 40, RED);
}

// Cek kalau mobil nyentuh finish line
bool CheckFinishLineCollision(Car* car) {
    return (car->y + car->height/2) <= (FINISH_LINE_Y + FINISH_LINE_HEIGHT);
}

// Free semua node + data
void FreeFinishLine(List* finishList) {
    // free masing-masing FinishTile dengan free()
    hapusList(finishList, free);
}
