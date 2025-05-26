#include "../include/skor.h"
#include "../include/config.h"
#include <stdio.h>
#include <raylib.h>

// Fungsi untuk menginisialisasi skor menjadi 0
void initSkor(Skor *skor)
{
    skor->nilai = 0; // Menetapkan nilai skor awal menjadi 0
}

// Fungsi untuk menambah poin ke skor
void tambahSkor(Skor *skor, int poin)
{
    if (poin > 0) // Pastikan poin yang ditambahkan adalah angka positif
    {
        skor->nilai += poin; // Menambahkan poin ke skor
    }
}

// Fungsi untuk mengurangi poin dari skor, tetapi tidak boleh kurang dari 0
void kurangiSkor(Skor *skor, int poin)
{
    if (poin > 0) // Pastikan poin yang dikurangi adalah angka positif
    {
        if (skor->nilai < poin) // Jika poin yang dikurangi lebih besar dari skor yang ada
        {
            skor->nilai = 0; // Set skor menjadi 0 jika kurang dari poin yang dikurangi
        }
        else
        {
            skor->nilai -= poin; // Mengurangi skor dengan poin
        }
    }
}

// Fungsi untuk mengambil nilai skor saat ini
int getSkor(const Skor *skor)
{
    return skor->nilai; // Mengembalikan nilai skor saat ini
}

// Fungsi untuk menampilkan skor di layar menggunakan Raylib
void tampilkanSkor(const Skor *skor)
{
    char skorText[50];  // Mendeklarasikan array untuk menyimpan teks skor
    snprintf(skorText, sizeof(skorText), "Skor: %d", skor->nilai);  // Menyusun teks untuk skor
    DrawText(skorText, 10, 10, 20, WHITE); // Menampilkan teks skor di posisi kiri atas layar
}

// FIXED: Implementasi fungsi resetSkor yang hilang
void resetSkor(Skor *skor)
{
    if (skor) {
        skor->nilai = 0; // Reset skor menjadi 0
    }
}

// FIXED: Implementasi fungsi freeSkor yang hilang
void freeSkor(Skor *skor)
{
    // Untuk struct sederhana seperti Skor, tidak perlu free memory khusus
    // Tapi kita bisa reset nilai untuk safety
    if (skor) {
        skor->nilai = 0;
    }
    // Note: Fungsi ini tetap diperlukan untuk konsistensi dengan interface
    // meskipun struct Skor tidak mengalokasi memory dinamis
}