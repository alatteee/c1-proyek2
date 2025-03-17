#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>

// Struktur untuk menyimpan nilai skor
typedef struct {
    int nilai; // Nilai skor pemain
} Skor;

// Inisialisasi skor
void initSkor(Skor *skor);

// Menambah poin ke skor
void tambahSkor(Skor *skor, int poin);

// Mengurangi poin dari skor (tidak boleh negatif)
void kurangiSkor(Skor *skor, int poin);

// Mengambil nilai skor saat ini
int getSkor(const Skor *skor);

// Menampilkan skor ke dalam log Raylib
void tampilkanSkor(const Skor *skor);

#endif // SKOR_H
