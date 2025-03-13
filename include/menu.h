#ifndef MENU_H
#define MENU_H

#include "raylib.h"

// Jumlah opsi menu
#define NUM_OPTIONS 3

// Deklarasi fungsi
void DrawMenu(int selectedOption);
int UpdateMenu(int selectedOption);

#endif