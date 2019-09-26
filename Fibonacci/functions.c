#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "definitions.h"

void * getSeries(threadInformation info) {
    info->array = prepareFibonacciArray();
    int * auxiliarPointer = info->array;
    for(int index = 0; index < info->seriesLimit; index++) {
        int currentTerm = fibonacci(index);
        if (currentTerm <= info->seriesLimit) {
            *auxiliarPointer = currentTerm;
            auxiliarPointer++;
        } else  index = info->seriesLimit + 3;  
    }
    return info;
}

int * prepareFibonacciArray() {
    int * newArray = (int *)malloc(sizeof(int)*ARRAY_SIZE);
    int * auxiliarArray = newArray;
    if (newArray == NULL) {
        printf("Error while creating array\n");
        exit(0);
    }
    for(int index = 0; index < ARRAY_SIZE ; index++, auxiliarArray++) * auxiliarArray = FINAL;
    return newArray;
}

pthread_t * createDinamicArray(int numberOfThreads) {
    pthread_t * newArray = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);
    if(newArray == NULL) {
        printf("Error while creating array \n");
		exit(0);
	}
	return newArray;
}

threadInformation * createStructInformation(int numberOfThreads) {
    threadInformation * array = (threadInformation *)malloc(sizeof(threadStruct)*numberOfThreads); 
    if(array == NULL) {
        printf("Error while creating struct");
        exit(0);
    }
    for(int index = 0; index < numberOfThreads; index++) {
        array[index] = (threadInformation)malloc(sizeof(threadStruct));
        if(array[index] == NULL) {
            printf("Error while creating struct");
            exit(0);
        }
    }
    return array;
}

int fibonacci(int term) {
    if(term==0 || term==1)
		return term;
	else
		return fibonacci(term-2) + fibonacci(term-1);
}