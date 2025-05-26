#include "../include/finish_line.h"
#include "../include/config.h"
#include <stdlib.h>

// Membuat segmen finish line
FinishLineSegment *createFinishLineSegment(int x, int y, int width, int height, Color color)
{
  FinishLineSegment *segment = malloc(sizeof(FinishLineSegment));
  if (segment)
  {
    segment->x = x;
    segment->y = y;
    segment->width = width;
    segment->height = height;
    segment->color = color;
  }
  return segment;
}

// Membebaskan segmen finish line
void freeFinishLineSegment(void *data)
{
  if (data)
  {
    free(data);
  }
}

// Menggambar segmen finish line
void drawFinishLineSegment(void *data)
{
  FinishLineSegment *segment = (FinishLineSegment *)data;
  DrawRectangle(segment->x, segment->y, segment->width, segment->height, segment->color);
}

// Membuat list segmen finish line
List *createFinishLineSegments(void)
{
  List *segments = buatList();

  int squareSize = 20; // Ukuran kotak untuk pola checkerboard

  // Membuat pola checkerboard untuk finish line
  for (int i = 0; i < SCREEN_WIDTH / squareSize; i++)
  {
    for (int j = 0; j < 2; j++)
    { // 2 baris kotak
      int x = i * squareSize;
      int y = FINISH_LINE_Y + (j * squareSize);

      // Tentukan warna berdasarkan posisi (pola checkerboard)
      Color squareColor = ((i + j) % 2 == 0) ? WHITE : BLACK;

      FinishLineSegment *segment = createFinishLineSegment(x, y, squareSize, squareSize, squareColor);
      if (segment)
      {
        tambahData(segments, segment);
      }
    }
  }

  // Tambahkan border atas dan bawah
  FinishLineSegment *topBorder = createFinishLineSegment(0, FINISH_LINE_Y - 2, SCREEN_WIDTH, 2, RED);
  FinishLineSegment *bottomBorder = createFinishLineSegment(0, FINISH_LINE_Y + (2 * squareSize), SCREEN_WIDTH, 2, RED);

  if (topBorder)
    tambahData(segments, topBorder);
  if (bottomBorder)
    tambahData(segments, bottomBorder);

  return segments;
}

// Menggambar garis finish menggunakan single linked list
void DrawFinishLine(void)
{
  static List *finishLineSegments = NULL;

  // Buat segmen hanya sekali
  if (!finishLineSegments)
  {
    finishLineSegments = createFinishLineSegments();
  }

  // Gambar semua segmen
  tampilkanList(finishLineSegments, drawFinishLineSegment);
}

// Fungsi untuk memeriksa apakah mobil telah melewati garis finish
bool CheckFinishLineCollision(Car *car)
{
  // Cek apakah posisi Y mobil telah melewati atau mencapai garis finish
  if (car->y <= FINISH_LINE_Y + FINISH_LINE_HEIGHT)
  {
    return true; // Pemain mencapai garis finish
  }
  return false; // Pemain belum mencapai garis finish
}