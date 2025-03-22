#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>
#include "config.h"

// Struktur untuk menyimpan nilai skor pemain
typedef struct {
    int nilai; // Nilai skor pemain
} Skor;

// Fungsi untuk menginisialisasi nilai skor
void initSkor(Skor *skor);

// Fungsi untuk menambah poin ke nilai skor
void tambahSkor(Skor *skor, int poin);

// Fungsi untuk mengurangi poin dari nilai skor (tidak boleh menjadi nilai negatif)
void kurangiSkor(Skor *skor, int poin);

// Fungsi untuk mengambil nilai skor saat ini
int getSkor(const Skor *skor);

// Fungsi untuk menampilkan nilai skor ke dalam log Raylib
void tampilkanSkor(const Skor *skor);

#endif // SKOR_H