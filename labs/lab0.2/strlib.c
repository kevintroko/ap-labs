#include <stdio.h>

int counter = 0;

int strlen2(char *str) {
    for (int i = 0 ; str[i]!='\0'; i++)
    {
        counter++;
    }
    
    printf("Counter is %d", counter);
    return counter;
}


