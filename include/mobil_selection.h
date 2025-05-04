#ifndef MOBIL_SELECTION_H
#define MOBIL_SELECTION_H

#include "mobil.h"

// Struktur untuk node linked list mobil
typedef struct CarNode {
    Car car;                      // Data mobil
    char name[50];                // Nama mobil (misal "Sport Merah")
    struct CarNode *next;         // Pointer ke node berikutnya
} CarNode;

// Fungsi untuk inisialisasi daftar mobil
CarNode* createCarList();

// Fungsi untuk gambar pilihan mobil
void drawCarSelection(CarNode *head, int selectedIndex, Texture2D background);

// Fungsi untuk ambil mobil terpilih
CarNode* getCarByIndex(CarNode *head, int index);

// Fungsi untuk hitung jumlah mobil di list
int countCars(CarNode *head);

// Fungsi untuk hapus semua mobil
void freeCarList(CarNode *head);

#endif
