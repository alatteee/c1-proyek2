#include "../include/high_score.h"
#include "../include/config.h"

// Tambahkan node ke linked list dengan urutan menurun (descending)
void InsertSorted(HighScoreNode **head, const char *name, int score)
{
    HighScoreNode *newNode = (HighScoreNode *)malloc(sizeof(HighScoreNode));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->next = NULL;

    if (*head == NULL || score > (*head)->score)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    HighScoreNode *current = *head;
    while (current->next != NULL && current->next->score >= score)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Simpan linked list ke file
void SaveHighScore(const char *name, int score)
{
    HighScoreNode *head = NULL;
    LoadHighScores(&head);

    InsertSorted(&head, name, score);

    // Pangkas jika lebih dari MAX_HIGH_SCORES
    HighScoreNode *current = head;
    int count = 1;
    while (current && current->next)
    {
        if (count == MAX_HIGH_SCORES)
        {
            FreeHighScores(current->next);
            current->next = NULL;
            break;
        }
        current = current->next;
        count++;
    }

    FILE *file = fopen("highscores.txt", "w");
    if (file)
    {
        current = head;
        while (current)
        {
            fprintf(file, "%s %d\n", current->name, current->score);
            current = current->next;
        }
        fclose(file);
    }

    FreeHighScores(head);
}

// Memuat skor dari file ke linked list
void LoadHighScores(HighScoreNode **head)
{
    FILE *file = fopen("highscores.txt", "r");
    if (file)
    {
        char name[MAX_NAME_LENGTH];
        int score;

        while (fscanf(file, "%s %d", name, &score) == 2)
        {
            InsertSorted(head, name, score);
        }

        fclose(file);
    }
}

// Menggambar high scores ke layar
void DrawHighScores(Texture2D brickTexture)
{
    HighScoreNode *head = NULL;
    LoadHighScores(&head);

    DrawTexture(brickTexture, 0, 0, WHITE);
    const char *title = "High Scores";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, SCREEN_WIDTH / 2 - titleWidth / 2, 200, 40, WHITE);

    HighScoreNode *current = head;
    int i = 0;
    while (current && i < MAX_HIGH_SCORES)
    {
        char scoreText[50];
        snprintf(scoreText, sizeof(scoreText), "%d. %s - %d", i + 1, current->name, current->score);
        int scoreWidth = MeasureText(scoreText, 20);
        DrawText(scoreText, SCREEN_WIDTH / 2 - scoreWidth / 2, 250 + i * 28, 20, WHITE);
        current = current->next;
        i++;
    }

    FreeHighScores(head);
}

// Bebaskan memori
void FreeHighScores(HighScoreNode *head)
{
    HighScoreNode *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
