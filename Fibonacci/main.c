#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "definitions.h"

void printInformation(threadInformation info);
void printArrays(int * array);


int main(int argc, char ** argv) {
    if (argc < 3) {
        printf("I'm sorry, you must add at least 2 arguments \n");
    } else {
        int numberOfThreads = atoi(argv[1]);
        void * returnValue;
        pthread_t *threadArray = createDinamicArray(numberOfThreads);
        threadInformation * currentThreadInformation = createStructInformation(numberOfThreads); 
        for(int index = 0 ; index < numberOfThreads ; index ++) {
            currentThreadInformation[index]->seriesLimit = atoi(argv[index + 2]);
            currentThreadInformation[index]->threadReference = (int *) &threadArray[index];        
        }
        for(int index = 0 ; index < numberOfThreads ; index ++) {
            pthread_create(&threadArray[index], NULL, (void *)getSeries, currentThreadInformation[index]);
        }
        for(int index = 0; index < numberOfThreads; index++) {
            pthread_join(threadArray[index], &returnValue);
            currentThreadInformation[index] = (threadInformation)returnValue;
            printInformation(currentThreadInformation[index]);
        }
    }
    return 0;
}

void printInformation(threadInformation info) {
    printf("\n*-----------------------------------------------------------------------------------------------------*\n");
    printf("\nThread %d has the limit %d and its fibonacci series is:\n\n", *(info->threadReference), info->seriesLimit);
    printArrays(info->array);
    printf("\n");
    printf("*-----------------------------------------------------------------------------------------------------*\n\n");
}

void printArrays(int * array) {
    for (; *array != FINAL ; array++) {
        printf("%d    ", *array);
    }
    printf("\n");
}
