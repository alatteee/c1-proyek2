#include "../include/mobil_selection.h"
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

CarNode* createCarNode(const char* name, const char* texturePath, float x, float y, float w, float h, int speed) {
    CarNode *node = (CarNode *)malloc(sizeof(CarNode));
    if (node) {
        initCar(&node->car, x, y, w, h, speed, texturePath);
        strncpy(node->name, name, sizeof(node->name));
        node->name[sizeof(node->name)-1] = '\0';
        node->next = NULL;
    }
    return node;
}

CarNode* createCarList() {
    CarNode *head = NULL;
    CarNode *last = NULL;

    // Isi daftar mobil
    CarNode *mobil1 = createCarNode("Mobil Biasa Biru", "resources/mobil/biasa_biru.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    CarNode *mobil2 = createCarNode("Mobil Biasa Kuning", "resources/mobil/biasa_kuning.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    CarNode *mobil3 = createCarNode("Mobil Biasa Merah", "resources/mobil/biasa_red.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    CarNode *mobil4 = createCarNode("Mobil Sport Biru", "resources/mobil/sport_biru.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    CarNode *mobil5 = createCarNode("Mobil Sport Merah", "resources/mobil/sport_red.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);
    CarNode *mobil6 = createCarNode("Mobil Sport Kuning", "resources/mobil/sport_yellow.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10);

    // Sambungkan node-node
    head = mobil1;
    mobil1->next = mobil2;
    mobil2->next = mobil3;
    mobil3->next = mobil4;
    mobil4->next = mobil5;
    mobil5->next = mobil6;

    return head;
}

void drawCarSelection(CarNode *head, int selectedIndex, Texture2D background) {
    // Gambar background
    DrawTexture(background, 0, 0, WHITE);

    // Judul
    DrawText("Select Your Car..", SCREEN_WIDTH/2 - MeasureText("Select Your Car..", 30)/2, 90, 30, YELLOW);

    // Daftar mobil
    int startY = 250;    // Naikkan lebih ke atas
    int spacing = 40;    // Spasi antar mobil lebih kecil
    int fontSize = 20;   // Ukuran font lebih kecil

    int index = 0;
    CarNode *current = head;
    while (current != NULL) {
        Color color = (index == selectedIndex) ? RED : WHITE;
        DrawText(current->name, SCREEN_WIDTH/2 - MeasureText(current->name, fontSize)/2, startY + index * spacing, fontSize, color);
        current = current->next;
        index++;
    }
}


CarNode* getCarByIndex(CarNode *head, int index) {
    int i = 0;
    CarNode *current = head;
    while (current != NULL) {
        if (i == index)
            return current;
        current = current->next;
        i++;
    }
    return NULL;
}

int countCars(CarNode *head) {
    int count = 0;
    CarNode *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void freeCarList(CarNode *head) {
    CarNode *current = head;
    while (current != NULL) {
        CarNode *temp = current;
        current = current->next;
        unloadCarTexture(&temp->car); // Unload texture mobil
        free(temp);
    }
}
