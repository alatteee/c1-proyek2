#include "../include/single_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

// Node internal, tidak diekspos di header
typedef struct Node {
    void         *data;
    struct Node  *next;
} Node;

// Definisi struct List sesuai opaque type di header
struct List {
    Node *head;
    int   size;
};

List* buatList(void) {
    List *list = malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

void hapusList(List *list, void (*freeData)(void*)) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        if (freeData) freeData(tmp->data);
        free(tmp);
    }
    free(list);
}

void tambahData(List *list, void *data) {
    if (!list) return;
    Node *baru = malloc(sizeof(Node));
    if (!baru) return;
    baru->data = data;
    baru->next = NULL;

    if (list->head == NULL) {
        list->head = baru;
    } else {
        Node *curr = list->head;
        while (curr->next)
            curr = curr->next;
        curr->next = baru;
    }
    list->size++;
}

void* hapusJika(List *list, bool (*pred)(void*), void (*freeData)(void*)) {
    if (!list || !list->head) return NULL;
    Node *curr = list->head, *prev = NULL;
    while (curr) {
        if (pred(curr->data)) {
            if (prev) prev->next = curr->next;
            else      list->head = curr->next;
            list->size--;

            void *d = curr->data;
            free(curr);

            if (freeData) {
                freeData(d);
                return NULL;
            }
            return d;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void* cariData(List *list, bool (*pred)(void*)) {
    if (!list) return NULL;
    Node *curr = list->head;
    while (curr) {
        if (pred(curr->data))
            return curr->data;
        curr = curr->next;
    }
    return NULL;
}

void *ambilData(List *list, int index) {
    if (!list || index < 0) return NULL;
    Node *curr = list->head;
    int i = 0;
    while (curr) {
        if (i++ == index) return curr->data;
        curr = curr->next;
    }
    return NULL;
}


void tampilkanList(List *list, void (*printFn)(void*)) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        printFn(curr->data);
        curr = curr->next;
    }
}

int ukuranList(List *list) {
    return list ? list->size : 0;
}

bool listKosong(List *list) {
    return !list || list->size == 0;
}

void tambahDataTerurut(List *list, void *data,
        int (*cmp)(const void *a, const void *b)) {
    if (!list) return;
    // buat node baru
    Node *baru = malloc(sizeof *baru);
    baru->data = data;
    // posisi head?
    if (!list->head || cmp(data, list->head->data) < 0) {
    baru->next = list->head;
    list->head = baru;
    } else {
    Node *cur = list->head;
    while (cur->next && cmp(data, cur->next->data) >= 0)
    cur = cur->next;
    baru->next = cur->next;
    cur->next  = baru;
    }
    list->size++;
}
