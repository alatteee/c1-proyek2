#include "../include/mobil_selection.h"
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// Define missing constants
#define PLAYER_CAR_WIDTH 100  
#define PLAYER_CAR_HEIGHT 200 
#define SCREEN_WIDTH 800      

// Helper function to create and initialize car data
CarData* createCarData(const char *name, const char *texturePath, float x, float y, float w, float h, int speed) {
    CarData *carData = (CarData *)malloc(sizeof(CarData));
    if (carData) {
        initCar(&carData->car, x, y, w, h, speed, texturePath);
        strncpy(carData->name, name, sizeof(carData->name));
        carData->name[sizeof(carData->name) - 1] = '\0';
    }
    return carData;
}

// Helper function to free car data
void freeCarData(void *data) {
    if (data) {
        CarData *carData = (CarData*)data;
        unloadCarTexture(&carData->car);
        free(carData);
    }
}

List* createCarList() {
    List *carList = buatList();
    
    // Add cars to the list
    tambahData(carList, createCarData("Mobil Biasa Biru", "resources/mobil/biasa_biru.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    tambahData(carList, createCarData("Mobil Biasa Kuning", "resources/mobil/biasa_kuning.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    tambahData(carList, createCarData("Mobil Biasa Merah", "resources/mobil/biasa_red.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    tambahData(carList, createCarData("Mobil Sport Biru", "resources/mobil/sport_biru.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    tambahData(carList, createCarData("Mobil Sport Merah", "resources/mobil/sport_red.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    tambahData(carList, createCarData("Mobil Sport Kuning", "resources/mobil/sport_yellow.png", 0, 0, PLAYER_CAR_WIDTH, PLAYER_CAR_HEIGHT, 10));
    
    return carList;
}

void drawCarSelection(List *carList, int selectedIndex, Texture2D background) {
    // Gambar background
    DrawTexture(background, 0, 0, WHITE);

    // Judul
    DrawText("Select Your Car...", 500, 200, 30, YELLOW); // langsung atur nilai X dan Y manual

    // Area preview mobil (pindah ke sebelah kiri)
    int previewX = 460;  // Posisi X di sebelah kiri
    int previewY = 300;  // Posisi Y di tengah tampilan mobil
    int previewMaxWidth = 150;  // Lebar preview lebih besar
    int previewMaxHeight = 120; // Tinggi preview lebih besar
    
    // Posisi daftar mobil (sekarang lebih ke tengah)
    int listX = 620; // Posisi X menu daftar mobil
    int startY = 280;    // Posisi Y awal daftar
    int spacing = 50;    // Spasi antar mobil
    int fontSize = 24;   // Ukuran font

    int count = ukuranList(carList);
    
    // Gambar semua pilihan mobil
    for (int index = 0; index < count; index++) {
        CarData *carData = (CarData*)ambilData(carList, index);
        if (!carData) continue;
        
        // Pilihan menu - highlight yang dipilih
        Color color = (index == selectedIndex) ? RED : WHITE;
        DrawText(carData->name, listX, startY + index * spacing, fontSize, color);
        
        // Tampilkan preview mobil yang sedang dipilih
        if (index == selectedIndex) {
            // Hitung rasio aspek dari texture
            float aspectRatio = (float)carData->car.texture.width / (float)carData->car.texture.height;
            
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
                carData->car.texture,
                (Rectangle){0, 0, carData->car.texture.width, carData->car.texture.height},
                (Rectangle){previewX, previewY, displayWidth, displayHeight},
                (Vector2){0, 0},
                0.0f,
                WHITE);
                
            // Tambahkan teks keterangan di bawah preview
            DrawText("Preview", previewX, previewY + displayHeight + 10, 20, YELLOW);
        }
    }
    
    // Tambahkan instruksi navigasi
    DrawText("Press UP/DOWN to select", 500, 600, 20, WHITE);
    DrawText("Press ENTER to continue", 500, 640, 20, WHITE);

}

CarData* getCarByIndex(List *carList, int index) {
    return (CarData*)ambilData(carList, index);
}

void freeCarList(List *carList) {
    hapusList(carList, freeCarData);
}

// Count the number of cars in the list
int countCars(List *carList) {
    return ukuranList(carList);
}