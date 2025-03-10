#include <stdio.h>
#include "menu.h"

// Fungsi untuk menampilkan menu utama
void tampilkanMenu()
{
    int pilihan;

    do
    {
        printf("\n===== C1 Brick Racer =====\n");
        printf("1. Mulai Game\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            mulaiGame();
            break;
        case 2:
            keluarGame();
            break;
        default:
            printf("Pilihan tidak valid. Coba lagi!\n");
        }
    } while (pilihan != 2);
}

// Fungsi untuk mulai game (sementara placeholder)
void mulaiGame()
{
    printf("Game dimulai!\n");
}

// Fungsi untuk keluar dari game
void keluarGame()
{
    printf("Terima kasih telah bermain!\n");
}
