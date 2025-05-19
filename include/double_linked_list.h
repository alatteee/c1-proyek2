// double_list.h
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stddef.h>

// Node ganda
typedef struct DLNode {
    void         *data;
    struct DLNode *prev;
    struct DLNode *next;
} DLNode;

// List ganda
typedef struct {
    DLNode *head;
    DLNode *tail;
} DoubleList;

// Buat list baru (kosong)
DoubleList* dl_create(void);

// Hancurkan list + free tiap data via callback
void        dl_destroy(DoubleList *list, void (*freeData)(void*));

// Tambah data di akhir, kembalikan node-nya
DLNode*     dl_append(DoubleList *list, void *data);

// Hapus satu node spesifik, free data-nya via callback
void        dl_remove(DoubleList *list, DLNode *node, void (*freeData)(void*));

// Iterasi semua data
void        dl_for_each(DoubleList *list, void (*fn)(void*));

#endif // DOUBLE_LIST_H
