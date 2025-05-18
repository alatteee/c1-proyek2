#include "../include/menu.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "../include/config.h"
#include "../include/mobil.h"
#include "../include/skor.h"
#include "../include/rintangan.h"
#include "../include/level.h"
#include "../include/mobil_selection.h"
#include "../include/double_linked_list.h"
#include "../include/single_linked_list.h"


// Variabel global untuk menyimpan list dan current menu
DoubleList *menuList     = NULL;
MenuNode   *currentMenu  = NULL;
bool        isMusicEnabled = true;
Music       menuMusic; // di-load di main.c

// Callback untuk membebaskan satu MenuNode
void freeMenuNode(void *d) {
    MenuNode *m = d;
    if (m->data) free(m->data);  // payload
    free(m);
}

// Buat satu MenuNode baru (payload sudah dialok di caller)
MenuNode *CreateMenuNode(const char *title, GameState state,
                                void (*drawF)(void*),
                                void (*inputF)(GameState*),
                                void *data) {
    MenuNode *m = malloc(sizeof *m);
    if (!m) return NULL;
    strncpy(m->title, title, sizeof m->title-1);
    m->title[sizeof m->title-1] = '\0';
    m->state               = state;
    m->drawFunction        = drawF;
    m->handleInputFunction = inputF;
    m->data                = data;
    return m;
}

// Inisialisasi seluruh sistem menu
void InitializeMenuSystem(Texture2D brickTexture, List* levelList, List* carList)
{
    // Buat list kosong
    menuList = dl_create();

    // 1) Main Menu
    MainMenuData *d0 = malloc(sizeof *d0);
    d0->selectedOption = 0;
    d0->brickTexture   = brickTexture;
    dl_append(menuList, CreateMenuNode(
        "Main Menu", STATE_MENU,
        DrawMainMenu, HandleMainMenuInput,
        d0));

    // 2) Level Menu
    LevelMenuData *d1 = malloc(sizeof *d1);
    d1->selectedLevel = 0;
    d1->brickTexture  = brickTexture;
    d1->levelList     = levelList;
    dl_append(menuList, CreateMenuNode(
        "Level Menu", STATE_LEVEL_MENU,
        DrawLevelMenu, HandleLevelMenuInput,
        d1));

    // 3) Input Name
    InputNameData *d2 = malloc(sizeof *d2);
    memset(d2->playerName, 0, MAX_NAME_LENGTH);
    d2->brickTexture = brickTexture;
    dl_append(menuList, CreateMenuNode(
        "Input Name", STATE_INPUT_NAME,
        DrawInputNameMenu, HandleInputNameMenuInput,
        d2));

    // 4) Car Selection
    CarSelectionData *d3 = malloc(sizeof *d3);
    d3->selectedCarIndex = 0;
    d3->brickTexture     = brickTexture;
    d3->carList          = carList;
    dl_append(menuList, CreateMenuNode(
        "Car Selection", STATE_SELECT_CAR,
        DrawCarSelectionMenu, HandleCarSelectionMenuInput,
        d3));

    // 5) Settings
    SettingsData *d4 = malloc(sizeof *d4);
    d4->brickTexture = brickTexture;
    dl_append(menuList, CreateMenuNode(
        "Settings", STATE_SETTINGS,
        DrawSettingsMenu, HandleSettingsMenuInput,
        d4));

    // Set default current
    SetCurrentMenu(STATE_MENU);
}

// Bebaskan semua node menu
void FreeMenuSystem(void) {
    if (menuList) {
        dl_destroy(menuList, freeMenuNode);
        menuList    = NULL;
        currentMenu = NULL;
    }
}

// Cari dan set currentMenu berdasarkan state
void SetCurrentMenu(GameState state) {
    for (DLNode *n = menuList->head; n; n = n->next) {
        MenuNode *m = n->data;
        if (m->state == state) {
            currentMenu = m;
            return;
        }
    }
    // fallback ke head
    currentMenu = menuList->head ? menuList->head->data : NULL;
}

// Dispatcher input & draw
void HandleMenuInput(GameState *state) {
    if (currentMenu && currentMenu->handleInputFunction)
        currentMenu->handleInputFunction(state);
}
void DrawMenu(void) {
    if (currentMenu && currentMenu->drawFunction)
        currentMenu->drawFunction(currentMenu->data);
}

/* ====== SEMUA FUNGSI DRAW dan HANDLE INPUT DARI MENU ====== */

void DrawMainMenu(void *data) {
    MainMenuData *d = data;
    const char *opts[] = { "Start Game", "Settings", "Exit Game" };
    DrawTexture(d->brickTexture, 0, 0, WHITE);
    DrawText("C1 Brick Racer",
             (SCREEN_WIDTH - MeasureText("C1 Brick Racer", 40))/2,
             250, 40, WHITE);
    for (int i = 0; i < 3; i++) {
        int x = SCREEN_WIDTH/2-100, y = 300 + i*60;
        DrawRectangle(x, y, 200, 40,
            (i == d->selectedOption) ? RED : LIGHTGRAY);
        int tw = MeasureText(opts[i], 20);
        DrawText(opts[i], x + (200-tw)/2, y+10, 20, BLACK);
    }
}

void HandleMainMenuInput(GameState *state) {
    MainMenuData *d = currentMenu->data;
    if (IsKeyPressed(KEY_UP))   d->selectedOption = (d->selectedOption + 2) % 3;
    if (IsKeyPressed(KEY_DOWN)) d->selectedOption = (d->selectedOption + 1) % 3;
    if (IsKeyPressed(KEY_ENTER)) {
        switch (d->selectedOption) {
            case 0: *state = STATE_LEVEL_MENU; break;
            case 1: *state = STATE_SETTINGS;   break;
            case 2: *state = STATE_EXIT;       break;
        }
    }
}

void DrawLevelMenu(void *data) {
    LevelMenuData *d = data;
    DrawTexture(d->brickTexture, 0, 0, WHITE);
    DrawText("Select Level", (SCREEN_WIDTH - MeasureText("Select Level", 40)) / 2, 250, 40, WHITE);

    int total = ukuranList(d->levelList);
    int x = SCREEN_WIDTH / 2 - 100;
    int y = 300;

    for (int i = 0; i < total; i++) {
        Level *lvl = (Level *)ambilData(d->levelList, i);
        if (!lvl) continue;
        Color boxColor = (i == d->selectedLevel) ? RED : LIGHTGRAY;
        DrawRectangle(x, y + i * 60, 200, 50, boxColor);
        DrawText(lvl->name, x + 10, y + i * 60 + 10, 20, BLACK);
    }

    // Tombol Back di paling bawah
    Color backColor = (d->selectedLevel == total) ? RED : LIGHTGRAY;
    DrawRectangle(x, y + total * 60, 200, 50, backColor);
    DrawText("Back", x + (200 - MeasureText("Back", 20)) / 2, y + total * 60 + 10, 20, BLACK);
}


void HandleLevelMenuInput(GameState *state) {
    LevelMenuData *d = currentMenu->data;
    int cnt = ukuranList(d->levelList);  // jumlah level
    int totalOptions = cnt + 1;          // tambah 1 untuk Back

    if (IsKeyPressed(KEY_UP)) {
        d->selectedLevel = (d->selectedLevel - 1 + totalOptions) % totalOptions;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        d->selectedLevel = (d->selectedLevel + 1) % totalOptions;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (d->selectedLevel == cnt)  // terakhir: tombol Back
            *state = STATE_MENU;
        else
            *state = STATE_INPUT_NAME;
    }
}


void DrawInputNameMenu(void *data) {
    InputNameData *d = data;
    DrawTexture(d->brickTexture, 0, 0, WHITE);
    DrawText("Enter Your Name",
             (SCREEN_WIDTH - MeasureText("Enter Your Name",40))/2,
             250, 40, WHITE);
    DrawRectangle(SCREEN_WIDTH/2-100, 350, 200, 50, LIGHTGRAY);
    DrawText(d->playerName, SCREEN_WIDTH/2-90, 360, 20, BLACK);
    DrawText("ENTER to continue, ESC to back",
             (SCREEN_WIDTH-MeasureText("ENTER to continue, ESC to back",20))/2,
             450, 20, WHITE);
}

void HandleInputNameMenuInput(GameState *state) {
    InputNameData *d = currentMenu->data;
    int c = GetCharPressed();
    if (c > 0 && strlen(d->playerName) < MAX_NAME_LENGTH-1) {
        size_t len = strlen(d->playerName);
        d->playerName[len] = c;
        d->playerName[len+1] = '\0';
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(d->playerName)>0) {
        d->playerName[strlen(d->playerName)-1] = '\0';
    }
    if (IsKeyPressed(KEY_ENTER) && strlen(d->playerName)>0) {
        *state = STATE_SELECT_CAR;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        *state = STATE_LEVEL_MENU;
    }
}

void DrawCarSelectionMenu(void *data) {
    CarSelectionData *d = data;
    DrawTexture(d->brickTexture, 0, 0, WHITE);
    DrawText("Select Your Car", (SCREEN_WIDTH-MeasureText("Select Your Car",40))/2, 150, 40, WHITE);

    int total = countCars(d->carList);
    int startY = 250;

    for (int i = 0; i < total; i++) {
        CarData *cd = getCarByIndex(d->carList, i);
        int x = SCREEN_WIDTH/2 - 150;
        int y = startY + i*120;
        Color color = (i == d->selectedCarIndex) ? RED : LIGHTGRAY;

        DrawRectangle(x, y, 300, 100, color);
        DrawText(cd->name, x+120, y+40, 20, BLACK);

        // Preview mobil (di kiri)
        DrawTexture(cd->car.texture, x+10, y+10, WHITE);
    }

    // Back button
    int backY = startY + total*120;
    DrawRectangle(SCREEN_WIDTH/2 - 100, backY, 200, 50, LIGHTGRAY);
    DrawText("Back", SCREEN_WIDTH/2 - MeasureText("Back",20)/2, backY + 15, 20, BLACK);
}

void HandleCarSelectionMenuInput(GameState *state) {
    CarSelectionData *d = currentMenu->data;
    int total = countCars(d->carList);
    if (IsKeyPressed(KEY_UP)) {
        d->selectedCarIndex = (d->selectedCarIndex + total - 1) % total;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        d->selectedCarIndex = (d->selectedCarIndex + 1) % total;
    }
    if (IsKeyPressed(KEY_ENTER)) {
        *state = (d->selectedCarIndex < 0) ? STATE_INPUT_NAME : STATE_GAME;
    }
}

void DrawSettingsMenu(void *data) {
    SettingsData *d = data;
    DrawTexture(d->brickTexture, 0, 0, WHITE);
    DrawText("Settings",
             (SCREEN_WIDTH - MeasureText("Settings", 40)) / 2,
             250, 40, WHITE);

    const char *opt = isMusicEnabled ? "Music: On" : "Music: Off";

    Color color1 = (d->selectedOption == 0) ? RED : LIGHTGRAY;
    Color color2 = (d->selectedOption == 1) ? RED : LIGHTGRAY;

    DrawRectangle(SCREEN_WIDTH / 2 - 100, 350, 200, 50, color1);
    DrawText(opt,
        SCREEN_WIDTH / 2 - MeasureText(opt, 20) / 2, 365, 20, BLACK);

    DrawRectangle(SCREEN_WIDTH / 2 - 100, 430, 200, 50, color2);
    DrawText("Back",
        SCREEN_WIDTH / 2 - MeasureText("Back", 20) / 2, 445, 20, BLACK);
}

void HandleSettingsMenuInput(GameState *state) {
    SettingsData *d = currentMenu->data;

    if (IsKeyPressed(KEY_UP)) {
        d->selectedOption = (d->selectedOption + 1) % 2;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        d->selectedOption = (d->selectedOption + 1) % 2;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (d->selectedOption == 0) {
            isMusicEnabled = !isMusicEnabled;
            if (isMusicEnabled) PlayMusicStream(menuMusic);
            else StopMusicStream(menuMusic);
        } else if (d->selectedOption == 1) {
            *state = STATE_MENU;
        }
    }
}


