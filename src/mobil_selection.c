#include "../include/mobil_selection.h"
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// Define missing constants
#define PLAYER_CAR_WIDTH 100  // Adjust value based on your requirements
#define PLAYER_CAR_HEIGHT 200 // Adjust value based on your requirements
#define SCREEN_WIDTH 800      // Adjust value based on your requirements

CarNode *createCarNode(const char *name, const char *texturePath, float x, float y, float w, float h, int speed)
{
  CarNode *node = (CarNode *)malloc(sizeof(CarNode));
  if (node)
  {
    initCar(&node->car, x, y, w, h, speed, texturePath);
    strncpy(node->name, name, sizeof(node->name));
    node->name[sizeof(node->name) - 1] = '\0';
    node->next = NULL;
  }
  return node;
}

CarNode *createCarList()
{
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
    DrawText("Select Your Car...", SCREEN_WIDTH/2 - MeasureText("Select Your Car...", 30)/2, 90, 30, YELLOW);

    // Area preview mobil (pindah ke sebelah kiri)
    int previewX = 180;  // Posisi X di sebelah kiri
    int previewY = 280;  // Posisi Y di tengah tampilan mobil
    int previewMaxWidth = 150;  // Lebar preview lebih besar
    int previewMaxHeight = 120; // Tinggi preview lebih besar
    
    // Posisi daftar mobil (sekarang lebih ke tengah)
    int listX = SCREEN_WIDTH/2 - 100; // Posisi X menu daftar mobil
    int startY = 200;    // Posisi Y awal daftar
    int spacing = 50;    // Spasi antar mobil
    int fontSize = 24;   // Ukuran font

    int index = 0;
    CarNode *current = head;
    
    // Gambar semua pilihan mobil
    while (current != NULL) {
        // Pilihan menu - highlight yang dipilih
        Color color = (index == selectedIndex) ? RED : WHITE;
        DrawText(current->name, listX, startY + index * spacing, fontSize, color);
        
        // Tampilkan preview mobil yang sedang dipilih
        if (index == selectedIndex) {
            // Hitung rasio aspek dari texture
            float aspectRatio = (float)current->car.texture.width / (float)current->car.texture.height;
            
            // Tentukan ukuran tampilan dengan mempertahankan rasio aspek
            float displayWidth = previewMaxWidth;
            float displayHeight = displayWidth / aspectRatio;
            
            // Jika tinggi hasil terlalu besar, sesuaikan
            if (displayHeight > previewMaxHeight) {
                displayHeight = previewMaxHeight;
                displayWidth = displayHeight * aspectRatio;
            }
            
            // Gambar kotak kuning sebagai border di sekitar preview mobil
            Rectangle previewBox = {
                previewX - 20, 
                previewY - 20, 
                displayWidth + 40, 
                displayHeight + 40
            };
            DrawRectangleLinesEx(previewBox, 3, YELLOW);
            
            // Gambar preview mobil di tengah area preview
            DrawTexturePro(
                current->car.texture,
                (Rectangle){0, 0, current->car.texture.width, current->car.texture.height},
                (Rectangle){previewX, previewY, displayWidth, displayHeight},
                (Vector2){0, 0},
                0.0f,
                WHITE);
                
            // Tambahkan teks keterangan di bawah preview
            DrawText("Preview", previewX, previewY + displayHeight + 10, 20, YELLOW);
        }
        
        current = current->next;
        index++;
    }
    
    // Tambahkan instruksi navigasi
    DrawText("Press UP/DOWN to select", SCREEN_WIDTH/2 - MeasureText("Press UP/DOWN to select", 20)/2, 
             startY + (index + 1) * spacing, 20, WHITE);
    DrawText("Press ENTER to continue", SCREEN_WIDTH/2 - MeasureText("Press ENTER to continue", 20)/2, 
             startY + (index + 2) * spacing, 20, WHITE);
}

CarNode *getCarByIndex(CarNode *head, int index)
{
  int i = 0;
  CarNode *current = head;
  while (current != NULL)
  {
    if (i == index)
      return current;
    current = current->next;
    i++;
  }
  return NULL;
}

int countCars(CarNode *head)
{
  int count = 0;
  CarNode *current = head;
  while (current != NULL)
  {
    count++;
    current = current->next;
  }
  return count;
}

void freeCarList(CarNode *head)
{
  CarNode *current = head;
  while (current != NULL)
  {
    CarNode *temp = current;
    current = current->next;
    unloadCarTexture(&temp->car); // Unload texture mobil
    free(temp);
  }
}
