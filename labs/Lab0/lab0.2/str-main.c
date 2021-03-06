// static-linking.c
#include <stdio.h>

int strlen2(char *str);
char* stradd(char *origin, char *addition);
char* strfind(char *origin, char *substr);
 
int main(int argc, char *argv[])
{
    if(argc > 3){
        printf("Initial Lenght      : %d\n", strlen2(argv[1]));
        printf("New String          : %s\n", stradd(argv[1], argv[2]));
        printf("SubString was found : %s\n", strfind(stradd(argv[1], argv[2]), argv[3]));
    } else {
        printf("incorrrect amount of arguments");
    }
    return 0;
}

/*
./str-final.o originalVeryLongString Addition Add
Initial Lenght      : 22
New String          : originalVeryLongStringAddition
SubString was found : yes
*/