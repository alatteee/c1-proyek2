#include "../include/skor.h"
#include <stdio.h>
#include <raylib.h>

// Inisialisasi skor menjadi 0
void initSkor(Skor *skor)
{
    skor->nilai = 0;
}

// Menambah poin ke skor
void tambahSkor(Skor *skor, int poin)
{
    if (poin > 0)
    { // Pastikan poin yang ditambahkan positif
        skor->nilai += poin;
    }
}

// Mengurangi poin dari skor, tetapi tidak boleh kurang dari 0
void kurangiSkor(Skor *skor, int poin)
{
    if (poin > 0)
    { // Pastikan poin yang dikurangi positif
        if (skor->nilai < poin)
        {
            skor->nilai = 0; // Jika skor lebih kecil dari poin yang dikurangi, set ke 0
        }
        else
        {
            skor->nilai -= poin;
        }
    }
}

// Mengembalikan nilai skor saat ini
int getSkor(const Skor *skor)
{
    return skor->nilai;
}

// Menampilkan skor di layar menggunakan Raylib
void tampilkanSkor(const Skor *skor)
{
    char skorText[50];
    snprintf(skorText, sizeof(skorText), "Skor: %d", skor->nilai);
    DrawText(skorText, 10, 10, 20, WHITE); // Menampilkan teks di kiri atas layar
}