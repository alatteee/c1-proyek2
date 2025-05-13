#include "../include/skor.h"
#include <stdio.h>
#include <stdlib.h>

// Membuat node baru dengan nilai skor awal
NodeSkor* buatNodeSkor(int nilaiAwal) {
    NodeSkor *node = (NodeSkor*) malloc(sizeof(NodeSkor));
    node->skor.nilai = nilaiAwal;
    node->next = NULL;
    return node;
}

// Menambahkan node baru ke akhir linked list
void tambahNodeSkor(NodeSkor **head, int nilaiAwal) {
    NodeSkor *baru = buatNodeSkor(nilaiAwal);
    if (*head == NULL) {
        *head = baru;
    } else {
        NodeSkor *curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = baru;
    }
}

// Menampilkan semua skor di list
void tampilkanSemuaSkor(NodeSkor *head) {
    NodeSkor *curr = head;
    int i = 1;
    while (curr != NULL) {
        printf("Skor %d: %d\n", i, curr->skor.nilai);
        curr = curr->next;
        i++;
    }
}

// Menghapus semua node di list
void hapusSemuaSkor(NodeSkor **head) {
    NodeSkor *curr = *head;
    while (curr != NULL) {
        NodeSkor *hapus = curr;
        curr = curr->next;
        free(hapus);
    }
    *head = NULL;
}

// Menambahkan poin ke skor node
void tambahSkor(NodeSkor *node, int poin) {
    if (poin > 0) {
        node->skor.nilai += poin;
    }
}

// Mengurangi poin dari skor node
void kurangiSkor(NodeSkor *node, int poin) {
    if (poin > 0) {
        if (node->skor.nilai < poin) {
            node->skor.nilai = 0;
        } else {
            node->skor.nilai -= poin;
        }
    }
}

// Mengambil skor dari node
int getSkor(const NodeSkor *node) {
    return node->skor.nilai;
}
