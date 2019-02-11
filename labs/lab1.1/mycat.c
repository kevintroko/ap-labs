#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char *argv[])
{   
    char data[1000];
    // Return -1 on error
    int file = open(argv[1] , O_RDONLY); 
    if (file == -1)
        printf("ERROR WHILE OPENING FILE\n");

    int fd = read(file, data, 1000);

    if (fd < 0) {
        printf("Error!\n");
        return -1;
    }

    printf("%s\n", data);
    return 0;
}