#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef thread
#define thread

#define FINAL -1
#define ARRAY_SIZE 100

typedef struct {
    int  seriesLimit;
    int * threadReference;
    int * array;
}threadStruct;

typedef threadStruct * threadInformation;

int fibonacci(int term);
void * getSeries(threadInformation);
threadInformation * createStructInformation(int);
pthread_t * createDinamicArray(int);
int * prepareFibonacciArray();
int arrayLength(int * array);


#endif