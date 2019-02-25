#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;
char *pch;

int strlen2(char *str) {
    for (int i = 0 ; str[i]!='\0'; i++)
        counter++;
    return counter;
}

char* stradd(char *origin, char *addition){
    int originS = strlen(origin);
    int additionS = strlen(addition);
    char* final = malloc(originS+additionS+1);
    strcpy(final, origin);
    strcat(final, addition);
    return final;
}

char* strfind(char *origin, char *substr) {
    pch = strstr(origin , substr);
    if(pch!=NULL) return "yes";
    else return "no";
}
