/* ----------------------------------------------------------------------------- */
/* File        : finish_line.h                                                   */
/* Deskripsi   : File header untuk menangani logika dan rendering garis finish   */
/*              dalam game "C1 Brick Racer". Berisi deklarasi fungsi untuk       */
/*              menggambar garis finish dan memeriksa tabrakan mobil dengan     */
/*              garis finish.                                                   */
/* Pembuat     : Azkha Nazzala                                                  */
/* ----------------------------------------------------------------------------- */

#ifndef FINISH_LINE_H
#define FINISH_LINE_H

#include <raylib.h>  
#include "config.h"  // File konfigurasi game (ukuran layar, konstanta, dll.)
#include "mobil.h"   // File header untuk tipe data Car (mobil)

// Fungsi untuk menggambar garis finish di layar
void DrawFinishLine();

// Fungsi untuk memeriksa apakah mobil menabrak garis finish
// Parameter:
// - car: Pointer ke objek mobil (Car) yang akan diperiksa
// Return:
// - true jika mobil menabrak garis finish, false jika tidak
bool CheckFinishLineCollision(Car *car);

#endif