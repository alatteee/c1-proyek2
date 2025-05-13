// include/skor.h
#ifndef SKOR_H
#define SKOR_H

#include "single_linked_list.h"  // ADT List

typedef struct {
    int nilai;
} Skor;

// Buat dan hapus daftar skor
List* buatDaftarSkor(void);
void  hapusDaftarSkor(List *daftar);

// Operasi pada daftar
void  tambahSkorKeDaftar(List *daftar, int nilaiAwal);
void  tampilkanSemuaSkor(List *daftar);

// Manipulasi 1 elemen skor
void  tambahSkor     (Skor *s, int poin);
void  kurangiSkor    (Skor *s, int poin);
int   getSkor        (const Skor *s);

// Tampilkan 1 skor di layar (Raylib)
void  tampilkanSkor  (const Skor *s);
void initSkor(Skor *skor);

#endif // SKOR_H
