#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "logger.h"

// Use the multiplier.c file for your code
struct dotProductArgs
{
    int x;
    int k;
    int lock;
    int index;
    long *vec1;
    long *vec2;
};

#define THREADS_NUMBER 2000

// Your program should be able to receive one argument which will be know as NUM_BUFFERS 
///inside the program (e.g. ./multipler -n 8).
int NUM_BUFFERS;
//long **buffers An array of NUM_BUFFERS pointers to the available 
//buffers that will serve as temporal vectors for dot product operations.
long **buffers;
//pthread_mutex_t *mutexes Mutexes that will help to know which buffer is available
pthread_mutex_t *mutexes;
pthread_attr_t attr;
// long *result Will store the result of matA and matB multiplication
long result[4000000 + 1];
long *f_matA, *f_matB;


// long * readMatrix(char *filename) Reads matrix file and returns an long type array with content of matrix.
long *readMatrix(char *filename);
// long * getColumn(int col, long *matrix) Returns the specified array that represents a column in the matrix array.
long *getColumn(int col, long *matrix);
// long * getRow(int row, long *matrix) Returns the specified array that represents a row in the matrix array.
long *getRow(int row, long *matrix);
// int getLock() Search for an available buffer, if so it returns the available lock id which is the same buffer id, otherwise returns -1
int getLock(int threadID);
// int releaseLock(int lock) Releases a buffer and unlock the mutex. Returns 0 for successful unlock, otherwise -1.
int releaseLock(int lock);
// long dotProduct(long *vec1, long *vec2) Given 2 arrays of 2000 lenght, it calculates the dot product and returns it as a long type value.
void *dotProduct(void *args);
void *dotProductSerial(void *args);
// long * multiply(long *matA, long *matB) Here's where all the magic happens. Explained in Matrix multiplication section
long *multiply(long *f_matA, long *f_matB);
// int saveResultMatrix(long *result) Saves result matrix into a new result.dat file, return 0 for a successful operation, otherwise it will return -1
int saveResultMatrix(long *result);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        errorf("Usage: %s -n <buffers>\n", argv[0]);
        return -1;
    }
    
    NUM_BUFFERS = atoi(argv[2]);

    buffers = calloc(NUM_BUFFERS, sizeof(long *));
    for (int i = 0; i < NUM_BUFFERS; i++)
    {
        buffers[i] = calloc(1, sizeof(long));
    }

    mutexes = calloc(NUM_BUFFERS, sizeof(pthread_mutex_t));
    for (int i = 0; i < NUM_BUFFERS; i++)
    {
        pthread_mutex_init(&mutexes[i], NULL);
    }

// You will read a couple of files (matA.dat, matB.dat) 
// which contain data that will be used for the matrices multiplication. 
// It's an array that represents all matrix's rows in an one-dimension array.

    f_matA = readMatrix("matA.dat");
    f_matB = readMatrix("matB.dat");

    multiply(f_matA, f_matB);
    infof("Done\n");

    saveResultMatrix(result);

    free(buffers);
    free(f_matA);
    free(f_matB);

    for (int i = 0; i < NUM_BUFFERS; i++)
    {
        pthread_mutex_destroy(&mutexes[i]);
    }
    pthread_exit(NULL);
}

long *readMatrix(char *filename)
{
    int i = 1;
    size_t len = 0;
    ssize_t nread;
    char *line = NULL;
    long *res = calloc(4000000 + 1, sizeof(long));

    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        panicf("Error when opening file\n");
    }

    while ((nread = getline(&line, &len, fp)) != -1)
    {
        //fwrite(line, nread, 1, stdout);
        res[i++] = strtol(line, NULL, 10);
    }
    free(line);
    return res;
}

long *getRow(int row, long *matrix)
{
    long *res = calloc(2000 + 1, sizeof(long));
    for (int i = 1; i < 2000 + 1; i++)
    {
        res[i] = matrix[row * 2000 - 2000 + i];
    }
    return res;
}

long *getColumn(int col, long *matrix)
{
    long *res = calloc(2000 + 1, sizeof(long));
    for (int i = 1; i < 2000 + 1; i++)
    {
        res[i] = matrix[i * 2000 - 2000 + col];
    }
    return res;
}

int getLock(int threadID)
{
    int res = -1;
    int i = 0;
    while (res != 0)
    {
        res = pthread_mutex_trylock(&mutexes[i % NUM_BUFFERS]);
        if (res == 0)
        {
            warnf("Thread [%d] with locked number: %d\n", threadID, i%NUM_BUFFERS); 
            return i % NUM_BUFFERS;
        }
        i++;
    }
    return -1;
}

int releaseLock(int lock)
{
    int res = pthread_mutex_unlock(&mutexes[lock]);
    if (res == 0)
    {
        return 0;
    }
    return -1;
}

void *dotProduct(void *args)
{
    struct dotProductArgs *dpArgs = (struct dotProductArgs *)args;
    long temp = 0;
    int lock = getLock(dpArgs->index);
    dpArgs->vec1 = getRow(dpArgs->x, f_matA);
    dpArgs->vec2 = getColumn(dpArgs->k, f_matB);
    for (int i = 1; i < 2000 + 1; i++)
    {
        temp += dpArgs->vec1[i] * dpArgs->vec2[i];
    }
    // Free 
    free(dpArgs->vec1);
    free(dpArgs->vec2);
    buffers[dpArgs->lock][0] = temp;
    result[dpArgs->index] = buffers[dpArgs->lock][0];
    releaseLock(lock);
    return NULL;
}

long *multiply(long *f_matA, long *f_matB)
{
    pthread_attr_init(&attr);
    pthread_t threads[THREADS_NUMBER];
    struct dotProductArgs *dpArgsArr = calloc(4000000 + 1, sizeof(struct dotProductArgs));

    int i = 1;
    for (int x = 1; x < 2000 + 1; x++)
    {
        for (int k = 1; k < 2000 + 1; k++)
        {
            dpArgsArr[i].index = i;
            dpArgsArr[i].x = x;
            dpArgsArr[i].k = k;
            int err = pthread_create(&threads[i % THREADS_NUMBER], &attr, dotProduct, (void *)&dpArgsArr[i]);
            if (err != 0)
            {
                panicf("Error %d when creating thread %d", err, i);
                exit(-1);
            }
            pthread_detach(threads[i % THREADS_NUMBER]);
            i++;
        }
    }
}

int saveResultMatrix(long *result)
{
    FILE *fp = fopen("result.dat", "w");
    if (!fp)
    {
        panicf("Error opening file\n");
    }

    for (int i = 1; i < 4000000 + 1; i++)
    {
        char *temp = calloc(8, sizeof(char));
        sprintf(temp, "%ld", result[i]);
        fputs(temp, fp);
        fputc('\n', fp);
        free(temp);
    }
    return 0;
}