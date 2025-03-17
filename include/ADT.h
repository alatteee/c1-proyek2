#ifndef SCORE_ADT_H
#define SCORE_ADT_H

#include <stdbool.h>

// Struktur menyimpan skor dan tanggal dimainkan
typedef struct
{
  int score;
  char date[25]; // Format: "YYYY-MM-DD HH:MM:SS"
} ScoreRecord;

// Membuat ScoreRecord baru dengan skor yang diberikan dan tanggal saat ini
ScoreRecord CreateScoreRecord(int score);

// Menyimpan ScoreRecord ke file
bool SaveScoreRecord(const ScoreRecord *record, const char *filename);

// Membaca ScoreRecord dari file
bool LoadScoreRecord(const char *filename, ScoreRecord *record);

#endif // SCORE_ADT_H