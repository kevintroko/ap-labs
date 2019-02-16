#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define _GNU_SOURCE
#define REPORT_FILE "report.txt"

// DIC
#include <ctype.h>
#define MAX_WORDS 100000
#define DATA_SIZE 100000
// DIC

void analizeLog(char *logFile, char *report);
char* formatToken(char *token);

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
    // Variables
    char data[DATA_SIZE];
    FILE *fPtr;
    fPtr = fopen("data/tokens.txt", "w");
    if (fPtr == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    // File open
    fp = fopen("dmesg.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        char *s = line;
        char str[10000];
        strcpy(str, s);
        char *token = strtok(str, "]");
        token = formatToken(token);
        fprintf(fPtr, "%s\n", token);
        printf("%s: \n", token);
        printf("%s\n", line);
    }
    fclose(fPtr);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

    FILE *fptr;
    char path[100];
    int i2, len2, index2, isUnique2;
    // List of distinct words
    char words[MAX_WORDS][50];
    char word[50];
    // Count of distinct words
    int count[MAX_WORDS];
    /* Try to open file */
    fptr = fopen("data/tokens.txt", "r");
    /* Exit if file not opened successfully */
    if (fptr == NULL) {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }
    // Initialize words count to 0
    for (i2 = 0; i2 < MAX_WORDS; i2++)
        count[i2] = 0;

    printf("Report is generated at: [%s]\n", report);
}

char* formatToken(char *token) {
    token = strtok(NULL, " ");
    if (token[strlen(token) - 1] == ':' || token[strlen(token) - 1] == ']') {
        int i = 0;
        while (token[i] != '\0') {
            i++;
        }
        token[i - 1] = '\0';
    }
    if (token[0] == '[' || token[0] == '\t') {
        token++;
    }
    return token;
}