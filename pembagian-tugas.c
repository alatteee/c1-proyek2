#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMBERS 5

typedef struct {
    char name[50];
    char task[100];
} Member;

void assignTasks(Member members[]) {
    const char *names[MAX_MEMBERS] = {"Ersya", "Nike", "Ala", "Yazid", "Andin"};
    const char *tasks[MAX_MEMBERS] = {"Main Menu", "Jalur", "Jalur", "Rintangan", "Mobil"};

    for (int i = 0; i < MAX_MEMBERS; i++) {
        snprintf(members[i].name, sizeof(members[i].name), "%s", names[i]);
        snprintf(members[i].task, sizeof(members[i].task), "%s", tasks[i]);
    }
}

void displayTasks(Member members[]) {
    printf("\nPembagian Pengerjaan Game:\n");
    printf("================================\n");
    printf("| %-20s | %-15s |\n", "Nama", "Bagian");
    printf("================================\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("| %-20s | %-15s |\n", members[i].name, members[i].task);
    }
    printf("================================\n");
}

int main() {
    Member members[MAX_MEMBERS];

    assignTasks(members);
    displayTasks(members);

    return 0;
}
