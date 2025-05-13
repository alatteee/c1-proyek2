// mobil_selection.h
#ifndef MOBIL_SELECTION_H
#define MOBIL_SELECTION_H

#include "single_linked_list.h"
#include "mobil.h"
#include <raylib.h>

// Ini menggantikan CarNode
typedef struct {
    Car    car;
    char   name[50];
} CarData;

// Buat daftar mobil pakai ADT List
List*    createCarList(void);

// Gambar pilihan mobil
void     drawCarSelection(List *daftar, int selectedIndex, Texture2D bg);

// Ambil mobil terpilih
CarData* getCarByIndex(List *daftar, int index);

// Hitung jumlah mobil
int      countCars(List *daftar);

// Hapus semua mobil (free & unload texture)
void     freeCarList(List *daftar);

#endif
