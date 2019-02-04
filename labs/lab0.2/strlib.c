#include <string.h>
#include <stdio.h>

int counter = 0;
char *pch;

int strlen2(char *str) {
    for (int i = 0 ; str[i]!='\0'; i++)
        counter++;
    return counter;
}

char* stradd2(char *origin, char *addition){
    return origin;
}

char* strfind(char *origin, char *substr) {
    pch = strstr(origin , substr);
    // printf("origin : %s\n", origin);
    // printf("substr : %s\n", substr);
    // printf("pch    : %s\n", pch);

    if(pch!=NULL) return "yes";
    else return "no";
}
