#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "island.h"

// @Todo check if an struct is better
#define SIZE 5
#define TOP 9
#define LOW 1

// Create Island
int island[SIZE][SIZE];

// Main Function
int main() {
    srand(time(0)); 
    generateSeas();
    printIsland();
    return 0;
}

void generateSeas() {
     // Generate values for each island cell
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            // Make north sea
            if(i==0) {
                island[i][j] = 0;
            } 
            // Make west sea
            else if(j==0) {
                island[i][j] = 0;
            } 
            // Make east sea
            else if(j==(SIZE-1)) {
                island[i][j] = 0;
            } 
            // Make south sea
            else if(i==(SIZE-1)) {
                island[i][j] = 0;
            } 
            // Make land
            else {
                island[i][j] = (rand() % 
                (TOP - LOW + 1)) + LOW; 
            }
        }
    }
}

void printIsland() {
    printf("----------------\n");
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
                printf("[%d]", island[i][j]);
        }
        printf("\n");
    }
    printf("----------------\n");
}