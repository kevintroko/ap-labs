#include <stdio.h>

int island[10][10];

int main() {
    island[0][0] = 1;
    island[0][1] = 1;
    printf("hello %d\n", island[0][0]);
    return 1;
}