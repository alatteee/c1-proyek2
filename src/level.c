#include "../include/level.h"
#include "../include/single_linked_list.h"
#include <stdlib.h>
#include <string.h>

// Buat list baru
List* CreateLevelList(void) {
    return buatList();
}

// Tambah level baru ke list
void AppendLevel(List* list, const char* name, int speed) {
    Level* lvl = malloc(sizeof *lvl);
    if (!lvl) return;
    // salin nama dengan aman
    strncpy(lvl->name, name, MAX_LEVEL_NAME_LENGTH);
    lvl->name[MAX_LEVEL_NAME_LENGTH - 1] = '\0';
    lvl->obstacleSpeed = speed;
    tambahData(list, lvl);
}

// Ambil level berdasarkan index
Level* getLevelByIndex(List* list, int index) {
    return ambilData(list, index);
}

// Fungsi baru: buat dan isi List level bawaan
List *LoadDefaultLevels(void) {
    List *list = buatList();
    // AppendLevel sekarang terima List* bukan LevelNode*
    AppendLevel(list, "Easy",   5);
    AppendLevel(list, "Medium", 8);
    AppendLevel(list, "Hard",   12);
    return list;
}



// Bebaskan semua node dan data level
void FreeLevels(List* list) {
    // free() untuk setiap Level*
    hapusList(list, free);
}
