// static-linking.c
#include <stdio.h>

int strlen2(char *str);

int main()
{
    printf("Initial Lenght      : %d\n", strlen2("123456"));
    return 0;
}

/*
./str-final.o originalVeryLongString Addition Add
New String          : originalVeryLongStringAddition
SubString was found : yes
*/