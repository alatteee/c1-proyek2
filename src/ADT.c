#include "../include/ADT.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

ScoreRecord CreateScoreRecord(int score)
{
  ScoreRecord record;
  record.score = score;

  // Ambil waktu saat ini
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  // Format tanggal: "YYYY-MM-DD HH:MM:SS"
  strftime(record.date, sizeof(record.date), "%Y-%m-%d %H:%M:%S", t);

  return record;
}

bool SaveScoreRecord(const ScoreRecord *record, const char *filename)
{
  FILE *fp = fopen(filename, "w");
  if (!fp)
  {
    return false;
  }

  // Simpan skor dan tanggal dalam dua baris
  fprintf(fp, "%d\n", record->score);
  fprintf(fp, "%s\n", record->date);

  fclose(fp);
  return true;
}

bool LoadScoreRecord(const char *filename, ScoreRecord *record)
{
  FILE *fp = fopen(filename, "r");
  if (!fp)
  {
    return false;
  }

  // Baca skor dan tanggal
  if (fscanf(fp, "%d\n", &record->score) != 1)
  {
    fclose(fp);
    return false;
  }

  if (fgets(record->date, sizeof(record->date), fp) == NULL)
  {
    fclose(fp);
    return false;
  }

  // Hilangkan newline jika ada
  size_t len = strlen(record->date);
  if (len > 0 && record->date[len - 1] == '\n')
  {
    record->date[len - 1] = '\0';
  }

  fclose(fp);
  return true;
}