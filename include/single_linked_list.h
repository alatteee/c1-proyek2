// single_linked_list.h
#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <stdbool.h>

// Opaque type untuk list
typedef struct List List;

// Buat list baru (kosong)
List*   buatList(void);

// Hapus semua node + free data pakai callback freeData
void    hapusList(List* list, void (*freeData)(void*));

// Tambah data ke akhir list
void    tambahData(List* list, void* data);

// Hapus data pertama yang memenuhi predicate, free pakai freeData
void*   hapusJika(List* list, bool (*pred)(void*), void (*freeData)(void*));

// Cari data pertama yang memenuhi predicate
void*   cariData(List* list, bool (*pred)(void*));

// Ambil data pada posisi index (O(n))
void *ambilData(List *list, int index);

// Jalankan fungsi printFn untuk tiap data dalam list
void    tampilkanList(List* list, void (*printFn)(void*));

// Kembalikan jumlah elemen
int     ukuranList(List* list);

// Cek apakah list kosong
bool    listKosong(List* list);

void tambahDataTerurut(List *list, void *data,
    int (*cmp)(const void *a, const void *b));

#endif // SINGLE_LINKED_LIST_H