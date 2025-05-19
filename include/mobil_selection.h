#ifndef MOBIL_SELECTION_H
#define MOBIL_SELECTION_H

#include "mobil.h"
#include "single_linked_list.h"

// Car data structure to be stored in the List
typedef struct CarData {
    Car car;           // The car object
    char name[50];     // Name of the car
} CarData;

// Function to create a list of cars
List* createCarList();

// Function to draw car selection UI
void drawCarSelection(List *carList, int selectedIndex, Texture2D background);

// Function to get car data by index
CarData* getCarByIndex(List *carList, int index);

// Function to free car list and car data
void freeCarList(List *carList);

// Function to count the number of cars in the list
int countCars(List *carList);

#endif