#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

// Reference 1 from http://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
// Reference 2 from http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
// Be sure to run Linux

int main(int argc, char *args[]) {
    int x = 0;
    DIR *dirp;
    
    struct dirent *entry;
    // Suppoused to be "dev/ttys+num in mac but it didn't work"
    dirp = opendir("/dev/pts");
    
    while ((entry = readdir(dirp)) != NULL) {
        x = x + 1;
    }
    closedir(dirp);

    int file;
    char buffer[100];
    for (int i = 0; i < x; i++) {
        char tty[] = "/dev/pts/";
        sprintf(buffer, "%d", i);
        strcat(tty, buffer);
        file = open(tty, O_RDWR, 777);
        //Write message 
        for (int j = 1; j < argc; j++) {
            write(file, args[j], strlen(args[j]));
            write(file, " ", 1);
        }
        // Remember to close file 
        close(file);
    }
}