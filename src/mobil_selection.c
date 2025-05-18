// mobil_selection.c
#include "../include/mobil_selection.h"
#include <stdlib.h>
#include <string.h>

#define PLAYER_CAR_WIDTH  100
#define PLAYER_CAR_HEIGHT 200
#define SCREEN_WIDTH      800

// callback untuk free setiap CarData
static void freeCarData(void *d) {
    CarData *cd = d;
    unloadCarTexture(&cd->car);
    free(cd);
}

// Inisialisasi List berisi CarData*
List* createCarList(void) {
    List *lst = buatList();
    const struct {
        const char *name, *tex;
    } items[] = {
        { "Mobil Biasa Biru",    "resources/mobil/biasa_biru.png" },
        { "Mobil Biasa Kuning",  "resources/mobil/biasa_kuning.png" },
        { "Mobil Biasa Merah",   "resources/mobil/biasa_red.png" },
        { "Mobil Sport Biru",    "resources/mobil/sport_biru.png" },
        { "Mobil Sport Merah",   "resources/mobil/sport_red.png" },
        { "Mobil Sport Kuning",  "resources/mobil/sport_yellow.png" },
    };
    size_t count = sizeof items / sizeof *items;
    for (size_t i = 0; i < count; i++) {
        CarData *cd = malloc(sizeof *cd);
        initCar(&cd->car, 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10, items[i].tex);
        strncpy(cd->name, items[i].name, sizeof cd->name);
        cd->name[sizeof cd->name -1] = '\0';
        tambahData(lst, cd);
    }
    return lst;
}

void drawCarSelection(List *daftar, int selectedIndex, Texture2D bg) {
    DrawTexture(bg, 0, 0, WHITE);
    DrawText("Select Your Car...",
             SCREEN_WIDTH/2 - MeasureText("Select Your Car...",30)/2,
             90, 30, YELLOW);

    int previewX = 180, previewY = 280;
    int pw = 150, ph = 120;
    int listX = SCREEN_WIDTH/2 - 100, startY = 200, spacing = 50, fontSz = 24;
    int n = ukuranList(daftar);

    for (int i = 0; i < n; i++) {
        CarData *cd = ambilData(daftar, i);
        Color clr = (i == selectedIndex) ? RED : WHITE;
        DrawText(cd->name, listX, startY + i*spacing, fontSz, clr);
        if (i == selectedIndex) {
            float ar = (float)cd->car.texture.width / cd->car.texture.height;
            float dw = pw, dh = dw/ar;
            if (dh > ph) { dh = ph; dw = dh*ar; }
            Rectangle box = { previewX-20, previewY-20, dw+40, dh+40 };
            DrawRectangleLinesEx(box, 3, YELLOW);
            DrawTexturePro(cd->car.texture,
                           (Rectangle){0,0,cd->car.texture.width,cd->car.texture.height},
                           (Rectangle){previewX, previewY, dw, dh},
                           (Vector2){0,0}, 0.0f, WHITE);
            DrawText("Preview", previewX, previewY+dh+10, 20, YELLOW);
        }
    }
    DrawText("Press UP/DOWN to select",
             SCREEN_WIDTH/2 - MeasureText("Press UP/DOWN to select",20)/2,
             startY + (n+1)*spacing, 20, WHITE);
    DrawText("Press ENTER to continue",
             SCREEN_WIDTH/2 - MeasureText("Press ENTER to continue",20)/2,
             startY + (n+2)*spacing, 20, WHITE);
}

CarData *getCarByIndex(List *list, int index) {
    if (!list || index < 0 || index >= ukuranList(list)) return NULL;
    return (CarData *)ambilData(list, index);
}

int countCars(List *daftar) {
    return ukuranList(daftar);
}

void freeCarList(List *daftar) {
    hapusList(daftar, freeCarData);
}
