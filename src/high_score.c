#include "../include/high_score.h"
#include "../include/config.h"

// Helper function untuk membuat HighScoreData
HighScoreData* createHighScoreData(const char *name, int score) {
    HighScoreData *data = malloc(sizeof(HighScoreData));
    if (data) {
        strcpy(data->name, name);
        data->score = score;
    }
    return data;
}

// Helper function untuk membebaskan HighScoreData
void freeHighScoreData(void* data) {
    if (data) {
        free(data);
    }
}

// Comparison function untuk sorting (descending order)
int compareHighScore(const void *a, const void *b) {
    const HighScoreData *scoreA = (const HighScoreData*)a;
    const HighScoreData *scoreB = (const HighScoreData*)b;
    return scoreB->score - scoreA->score; // Descending order
}

// Print function untuk debugging
void printHighScore(void* data) {
    HighScoreData *score = (HighScoreData*)data;
    printf("%s: %d\n", score->name, score->score);
}

// Simpan skor ke file menggunakan single linked list
void SaveHighScore(const char *name, int score) {
    List *scoreList = buatList();
    
    // Load existing scores from file
    FILE *file = fopen("highscores.txt", "r");
    if (file) {
        char tempName[MAX_NAME_LENGTH];
        int tempScore;
        
        while (fscanf(file, "%s %d", tempName, &tempScore) == 2) {
            HighScoreData *data = createHighScoreData(tempName, tempScore);
            if (data) {
                tambahData(scoreList, data);
            }
        }
        fclose(file);
    }
    
    // Add new score
    HighScoreData *newScore = createHighScoreData(name, score);
    if (newScore) {
        tambahData(scoreList, newScore);
    }
    
    // Manual sorting since we're not modifying the ADT
    // Convert to array for sorting
    int listSize = ukuranList(scoreList);
    HighScoreData **scoreArray = malloc(listSize * sizeof(HighScoreData*));
    
    for (int i = 0; i < listSize; i++) {
        scoreArray[i] = (HighScoreData*)ambilData(scoreList, i);
    }
    
    // Simple bubble sort
    for (int i = 0; i < listSize - 1; i++) {
        for (int j = 0; j < listSize - i - 1; j++) {
            if (compareHighScore(scoreArray[j], scoreArray[j + 1]) > 0) {
                HighScoreData *temp = scoreArray[j];
                scoreArray[j] = scoreArray[j + 1];
                scoreArray[j + 1] = temp;
            }
        }
    }
    
    // Save back to file (only top MAX_HIGH_SCORES)
    file = fopen("highscores.txt", "w");
    if (file) {
        int count = (listSize < MAX_HIGH_SCORES) ? listSize : MAX_HIGH_SCORES;
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", scoreArray[i]->name, scoreArray[i]->score);
        }
        fclose(file);
    }
    
    free(scoreArray);
    hapusList(scoreList, freeHighScoreData);
}

// Menggambar high scores ke layar
void DrawHighScores(Texture2D brickTexture) {
    List *scoreList = buatList();
    
    // Load scores from file
    FILE *file = fopen("highscores.txt", "r");
    if (file) {
        char tempName[MAX_NAME_LENGTH];
        int tempScore;
        
        while (fscanf(file, "%s %d", tempName, &tempScore) == 2) {
            HighScoreData *data = createHighScoreData(tempName, tempScore);
            if (data) {
                tambahData(scoreList, data);
            }
        }
        fclose(file);
    }
    
    DrawTexture(brickTexture, 0, 0, WHITE);
    const char *title = "High Scores";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, SCREEN_WIDTH / 2 - titleWidth / 2, 200, 40, WHITE);
    
    int displayCount = (ukuranList(scoreList) < MAX_HIGH_SCORES) ? ukuranList(scoreList) : MAX_HIGH_SCORES;
    
    for (int i = 0; i < displayCount; i++) {
        HighScoreData *data = (HighScoreData*)ambilData(scoreList, i);
        if (data) {
            char scoreText[50];
            snprintf(scoreText, sizeof(scoreText), "%d. %s - %d", i + 1, data->name, data->score);
            int scoreWidth = MeasureText(scoreText, 20);
            DrawText(scoreText, SCREEN_WIDTH / 2 - scoreWidth / 2, 250 + i * 28, 20, WHITE);
        }
    }
    
    const char *instruction = "Press ENTER or ESC to return";
    int instructionWidth = MeasureText(instruction, 20);
    DrawText(instruction, SCREEN_WIDTH / 2 - instructionWidth / 2, 600, 20, WHITE);
    
    hapusList(scoreList, freeHighScoreData);
}