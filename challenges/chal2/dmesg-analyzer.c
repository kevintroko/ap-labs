#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    char data[10000];
    // Return -1 on error
    int file = open(logFile, O_WRONLY);

    if (file == -1)
        printf("ERROR WHILE OPENING FILE\n");

    int fd = read(file, data, 10000);

    printf("%s is \n", data);

    printf("Report is generated at: [%s]\n", report);
}
