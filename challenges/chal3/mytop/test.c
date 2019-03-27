#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100000

void printPID(char **argv);

void main(int argc, char **argv) {
   printPID(argv);
}

void getList() {
    // ls | grep '[0-9]'
    printf("%d\n", 1);
}

void printPID(char **argv) {
    getList();
    int pid;
    sscanf(argv[1], "%d", &pid);
    char filename[100000];
    sprintf(filename, "/proc/%d/stat", pid);
    FILE *f = fopen(filename, "r");

    int unused;
    char comm[1000];
    char state;
    int ppid;
    fscanf(f, "%d %s %c %d", &unused, comm, &state, &ppid);
    printf("PID | Parent |      Name     | State \n");
    printf("%d      %d     %s          %c\n", pid, ppid, comm, state);
    fclose(f);
}

// | PID  | Parent | Name   | State   | Memory  | #Threads | Open Files |
// | ---- | ------ | ------ | ------- | ------- | -------- | -----------|
// | 120  | 1      | sshd   | Active  | 120M    | 1        | 5          |