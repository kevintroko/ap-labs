#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "island.h"

// @Todo check if an struct for island is better
#define SIZE 5
#define TOP 9
#define LOW 1

// Ball Struct
struct ball {
    int x;
    int y;
};

// Create Island
int island[SIZE][SIZE];
int seaCount = 0;

// Main Function
int main() {
    // Randoms change every execution
    srand(time(0)); 
   
    generateSeas();
    generateBall();
    printIsland();

    displayInfo(seaCount);
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
                island[i][j] = getRandom(TOP, LOW); 
            }
        }
    }
}

int getRandom(int top, int low) {
    return (rand() % (top - low + 1)) + low;
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


void generateBall() {
    
    struct ball ball_test = {0};

    ball_test.x = getRandom(3,1);
    ball_test.y = getRandom(3,1);
   

    if(island[ball_test.x][ball_test.y] != 0) {
        printf("ball[%d,%d]: landed on hill [%d]\n", ball_test.x, ball_test.y, island[ball_test.x][ball_test.y]);
        if(island[ball_test.x][ball_test.y] != 0) {

            // west
            printf("west : %d\n", island[ball_test.x][ball_test.y-1]);

            // north
            printf("north: %d\n", island[ball_test.x-1][ball_test.y]);

            // south
            printf("south: %d\n", island[ball_test.x+1][ball_test.y]);

            // east
            printf("east: %d\n", island[ball_test.x][ball_test.y+1]);    
        }

    } else {
        printf(" landed on water [%d]\n", island[ball_test.x][ball_test.y]);
        seaCount++;
    }
}
