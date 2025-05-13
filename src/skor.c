// src/skor.c
#include "../include/skor.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// callback untuk free setiap Skor*
static void _freeSkor(void *d) {
    free(d);
}

// callback untuk print tiap Skor*
static void _printSkor(void *d) {
    Skor *s = d;
    printf("Skor: %d\n", s->nilai);
}

List* buatDaftarSkor(void) {
    return buatList();
}

void hapusDaftarSkor(List *daftar) {
    // free semua node + data via _freeSkor
    hapusList(daftar, _freeSkor);
}

void tambahSkorKeDaftar(List *daftar, int nilaiAwal) {
    Skor *s = malloc(sizeof *s);
    s->nilai = nilaiAwal;
    tambahData(daftar, s);
}

void tampilkanSemuaSkor(List *daftar) {
    // iterasi semua data dan print dengan _printSkor
    tampilkanList(daftar, _printSkor);
}

// manipulasi satu skor
void tambahSkor(Skor *s, int poin) {
    if (poin > 0) s->nilai += poin;
}

void kurangiSkor(Skor *s, int poin) {
    if (poin > 0) {
        s->nilai = (s->nilai < poin) ? 0 : s->nilai - poin;
    }
}

int getSkor(const Skor *s) {
    return s->nilai;
}

// tampilkan di layar pakai Raylib
void tampilkanSkor(const Skor *s) {
    char buf[32];
    sprintf(buf, "Score: %d", s->nilai);
    DrawText(buf, 10, 10, 20, WHITE);
}

void initSkor(Skor *s) {
    s->nilai = 0;
}