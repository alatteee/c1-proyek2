#ifndef SKOR_H
#define SKOR_H

// Struktur skor seperti sebelumnya
typedef struct {
    int nilai;
} Skor;

// Node dalam linked list
typedef struct NodeSkor {
    Skor skor;               // Menyimpan data skor
    struct NodeSkor *next;   // Penunjuk ke node berikutnya
} NodeSkor;

// Fungsi dasar untuk linked list skor
NodeSkor* buatNodeSkor(int nilaiAwal);
void tambahNodeSkor(NodeSkor **head, int nilaiAwal);
void tampilkanSemuaSkor(NodeSkor *head);
void hapusSemuaSkor(NodeSkor **head);

// Fungsi manipulasi skor dalam node tertentu
void tambahSkor(NodeSkor *node, int poin);
void kurangiSkor(NodeSkor *node, int poin);
int getSkor(const NodeSkor *node);

#endif
