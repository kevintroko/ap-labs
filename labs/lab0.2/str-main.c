// static-linking.c
#include <stdio.h>

int strlen(char *str);

// *char stradd(char *origin, char *addition);

int strfind(char *origin, char *substr);

int main()
{
    printf("strlen is %s\n", strlen('Hello'));
    printf("strlen is %s\n", strfind('Hello', 'hell'));
    return 0;
}