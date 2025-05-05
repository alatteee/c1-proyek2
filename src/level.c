// level.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/level.h"

LevelNode* CreateLevelNode(const char* name, int speed) {
    LevelNode* newNode = (LevelNode*)malloc(sizeof(LevelNode));
    if (!newNode) return NULL;

    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->obstacleSpeed = speed;
    newNode->next = NULL;

    return newNode;
}

void AppendLevel(LevelNode** head, const char* name, int speed) {
    LevelNode* newNode = CreateLevelNode(name, speed);
    if (!*head) {
        *head = newNode;
    } else {
        LevelNode* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void FreeLevels(LevelNode* head) {
    while (head) {
        LevelNode* temp = head;
        head = head->next;
        free(temp);
    }
}

void PrintLevels(LevelNode* head) {
    while (head) {
        printf("Level: %s, Speed: %d\n", head->name, head->obstacleSpeed);
        head = head->next;
    }
}

LevelNode* getLevelByIndex(LevelNode* head, int index) {
    int i = 0;
    while (head && i < index) {
        head = head->next;
        i++;
    }
    return head;
}
