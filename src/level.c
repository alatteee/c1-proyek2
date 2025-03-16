/* ----------------------------------------------------------------------------- */
/* File        : level.c                                                         */
/* Deskripsi   : File implementasi untuk mengelola level dalam game "C1 Brick    */
/*              Racer". Berisi definisi level-level yang tersedia, termasuk      */
/*              kecepatan rintangan, jumlah rintangan, dan posisi rintangan.    */
/* Pembuat     : Azkha Nazzala                                                  */
/* ----------------------------------------------------------------------------- */

#include "../include/config.h"  // Mengimpor file header konfigurasi game

// Array yang menyimpan data untuk setiap level dalam game
Level levels[NUM_LEVELS] = {
    // Level 1: Easy (Mudah)
    {
        5, // Kecepatan rintangan (obstacleSpeed)
        3, // Jumlah rintangan (numObstacles)
        "Easy", // Nama level
        {
            {100, 200}, // Posisi rintangan 1 (x, y)
            {150, 250}, // Posisi rintangan 2 (x, y)
            {200, 300}  // Posisi rintangan 3 (x, y)
        }
    },
    // Level 2: Medium (Sedang)
    {
        8, // Kecepatan rintangan (obstacleSpeed)
        5, // Jumlah rintangan (numObstacles)
        "Medium", // Nama level
        {
            {300, 400}, // Posisi rintangan 1 (x, y)
            {350, 450}, // Posisi rintangan 2 (x, y)
            {400, 500}, // Posisi rintangan 3 (x, y)
            {450, 550}, // Posisi rintangan 4 (x, y)
            {500, 600}  // Posisi rintangan 5 (x, y)
        }
    },
    // Level 3: Hard (Sulit)
    {
        12, // Kecepatan rintangan (obstacleSpeed)
        7, // Jumlah rintangan (numObstacles)
        "Hard", // Nama level
        {
            {500, 600}, // Posisi rintangan 1 (x, y)
            {550, 650}, // Posisi rintangan 2 (x, y)
            {600, 700}, // Posisi rintangan 3 (x, y)
            {650, 750}, // Posisi rintangan 4 (x, y)
            {700, 800}, // Posisi rintangan 5 (x, y)
            {750, 850}, // Posisi rintangan 6 (x, y)
            {800, 900}  // Posisi rintangan 7 (x, y)
        }
    }
};