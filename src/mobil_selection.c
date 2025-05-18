#include "../include/mobil_selection.h"
#include <stdlib.h>
#include <string.h>

#define PLAYER_CAR_WIDTH  100
#define PLAYER_CAR_HEIGHT 200
#define SCREEN_WIDTH      1280
#define SCREEN_HEIGHT     720

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
    ClearBackground(BLACK);

    // Gambar background
    DrawTexturePro(
        bg,
        (Rectangle){ 0, 0, bg.width, bg.height },
        (Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT },
        (Vector2){ 0, 0 },
        0.0f, WHITE
    );

    // Judul di tengah kotak atas
    const char *judul = "SELECT YOUR CAR";
    int fontTitle = 36;
    int textW = MeasureText(judul, fontTitle);
    int textH = fontTitle;

    int textX = 640 - textW / 2;
    int textY = 135 - textH / 2;
    DrawText(judul, textX, textY, fontTitle, YELLOW);

    // Posisi list dan layout
    int listX = SCREEN_WIDTH / 2 + 50;  // Geser list agak kanan
    int startY = 265;
    int spacing = 45, fontSize = 22;
    int pw = 150, ph = 120;
    int n = ukuranList(daftar);

    for (int i = 0; i < n; i++) {
        CarData *cd = ambilData(daftar, i);

        if (i == selectedIndex) {
            DrawRectangle(listX - 10, startY + i * spacing - 5,
                          260, spacing, Fade(YELLOW, 0.2f));
        }

        Color textColor = (i == selectedIndex) ? RED : WHITE;
        DrawText(cd->name, listX, startY + i * spacing, fontSize, textColor);

        // Preview mobil di kiri list, sejajar secara vertikal
        if (i == selectedIndex) {
            float ar = (float)cd->car.texture.width / cd->car.texture.height;
            float dw = pw, dh = dw / ar;
            if (dh > ph) { dh = ph; dw = dh * ar; }

            int previewX = listX - 250;
            int previewY = startY + i * spacing;

            Rectangle box = { previewX - 20, previewY - dh / 2 - 20, dw + 40, dh + 40 };
            DrawRectangleLinesEx(box, 3, YELLOW);
            DrawTexturePro(cd->car.texture,
                (Rectangle){ 0, 0, cd->car.texture.width, cd->car.texture.height },
                (Rectangle){ previewX, previewY - dh / 2, dw, dh },
                (Vector2){ 0, 0 }, 0.0f, WHITE);
            DrawText("Preview",
                previewX + (dw / 2) - MeasureText("Preview", 18) / 2,
                previewY + dh / 2 + 10, 18, YELLOW);
        }
    }

    // Petunjuk kontrol
    const char *navHint = "key UP/DOWN to navigate     ENTER to confirm";
    DrawText(navHint,
        SCREEN_WIDTH / 2 - MeasureText(navHint, 20) / 2,
        startY + (n + 2) * spacing, 20, LIGHTGRAY);
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
