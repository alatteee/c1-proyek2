// double_list.c
#include "../include/double_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Buat list baru
DoubleList* dl_create(void) {
    DoubleList *l = malloc(sizeof *l);
    if (!l) return NULL;
    l->head = l->tail = NULL;
    return l;
}

// Hancurkan: loop dari head, free data dan node
void dl_destroy(DoubleList *list, void (*freeData)(void*)) {
    if (!list) return;
    DLNode *cur = list->head;
    while (cur) {
        DLNode *next = cur->next;
        if (freeData) freeData(cur->data);
        free(cur);
        cur = next;
    }
    free(list);
}

// Append di tail
DLNode* dl_append(DoubleList *list, void *data) {
    DLNode *n = malloc(sizeof *n);
    if (!n) return NULL;
    n->data = data;
    n->next = NULL;
    n->prev = list->tail;
    if (list->tail) list->tail->next = n;
    else list->head = n;
    list->tail = n;
    return n;
}

// Remove node yang ditunjuk
void dl_remove(DoubleList *list, DLNode *node, void (*freeData)(void*)) {
    if (!list || !node) return;
    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;
    if (freeData) freeData(node->data);
    free(node);
}

// Panggil fn(data) untuk tiap node
void dl_for_each(DoubleList *list, void (*fn)(void*)) {
    for (DLNode *cur = list->head; cur; cur = cur->next) {
        fn(cur->data);
    }
}
