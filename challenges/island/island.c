#include <stdio.h>

// @Todo check if an struct is better
#define SIZE 5
#define TOP 0
#define LOW 9

// Main Function
int main() {
    // Create Island
    int island[SIZE][SIZE];

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

            else {
                island[i][j] = 2;
            }
        }
    }
    
    printf("----------------\n");
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
                printf("[%d]", island[i][j]);
        }
        printf("\n");
    }
    printf("----------------\n");

    return 0;
}