#include "../include/jalur.h"
#include <raylib.h>
#include "../include/config.h"

// Fungsi untuk menggambar jalur (lanes) di layar
void draw_lanes()
{
    int lane_width = SCREEN_WIDTH / MAX_LANES;  // Menghitung lebar setiap jalur berdasarkan lebar layar dan jumlah jalur

    // Loop untuk menggambar garis vertikal pada setiap posisi jalur
    for (int i = 1; i < MAX_LANES; i++)
    {
        int position_x = i * lane_width;  // Posisi X untuk setiap jalur

        // Loop untuk menggambar garis vertikal kecil yang membentuk garis jalur
        for (int y = 0; y < SCREEN_HEIGHT; y += 40)  // Loop untuk menggambar garis-garis vertikal dalam interval 40 pixel
        {
            // Menggambar garis vertikal untuk jalur di posisi X yang sesuai dan dalam interval Y
            DrawLine(position_x, y, position_x, y + 20, WHITE);  // Menggambar garis vertikal putih dengan panjang 20 pixel
        }
    }
}