#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_words {
    char *str;            
    int count;            
    struct s_words *next; 
} words;

words *create_words(char *word){
    words *newWord = malloc(sizeof(words));
    if (newWord != NULL) {
        newWord->str = (char *)malloc((strlen(word)) + 1);
        strcpy(newWord->str, word);
        newWord->str[strlen(word)] = '\0';
        newWord->count = 1;
        newWord->next = NULL;
    }
    return newWord;
}

words *add_word(words **wordList, char *word) { 
    if (!*wordList) {
        return *wordList = create_words(word);
    }
    words *temp = *wordList;
    while (temp->next != NULL) {
        if (strcmp(temp->str, word) == 0) {
            temp->count = temp->count + 1;
            return *wordList;
        } else
            temp = temp->next;
    }

    words *newWord = create_words(word);
    if (NULL != newWord) { 
        temp->next = newWord;
    }
    return newWord;
}

int main(int argc, char *argv[]) {
    FILE *file;
    words *linkList = NULL;
    char *delim = ";. ,*\t\n";
    int ch = 0;
    int word = 1;
    int k = 0;
    char thisword[100];
    file = fopen(argv[1], "r");
    if (file == 0) {
        printf("ERROR!\n");
        return 1;
    }
    while ((ch = fgetc(file)) != EOF) {
        if (strchr(delim, ch)) {
            if (word == 1) {
                word = 0;
                thisword[k] = '\0';
                if (add_word(&linkList, thisword)) {
                    k = 0;
                }
            }
        } else {
            word = 1;
            thisword[k++] = tolower(ch); /* make ch lowercase */
        }
    }

    printf("\nWords in %s\n------------------------\n", argv[1]);
    int counted = 0;
    while (linkList != NULL) {

        counted = linkList->count;

        if(counted > 3 && strcmp(linkList->str,"the")!=0
                       && strcmp(linkList->str,"i")!=0
                       && strcmp(linkList->str,"is")!=0
                       && strcmp(linkList->str,"their")!=0) {
            printf("%s %d \n", linkList->str, linkList->count);
        }

        linkList = linkList->next;
    }

    return 0;
}