#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "definitions.h"

void swap(int leftIndex, int rightIndex) {
    int temporalNumber = arrayOfNumbers[leftIndex];
    arrayOfNumbers[leftIndex] = arrayOfNumbers[rightIndex];
    arrayOfNumbers[rightIndex] = temporalNumber;
}

void  * sort(int * indexes) {
    int firstIndex = indexes[0]; int lastIndex = indexes[1];
    int pivot = arrayOfNumbers[lastIndex];
    int leftIndex = firstIndex;
    int rightIndex = lastIndex - 1;
    while(1) {
        // Left index
        while(1) {
            if(arrayOfNumbers[leftIndex] >= pivot) break;
            leftIndex++;
        }
        // Right index
        while(1) {
            if(arrayOfNumbers[rightIndex] <= pivot) break;
            rightIndex--;
        }
        if(leftIndex >= rightIndex) {
            swap(leftIndex, lastIndex);
            break;
        }
        if( (leftIndex >= arraySize) || (rightIndex < 0)) break;
        
        swap(leftIndex, rightIndex);
        leftIndex++; rightIndex--;
    }
    printf("\nI'm the thread %ld and I sorted the array since the position %d 'till the position %d \n\n", pthread_self(),firstIndex, lastIndex);
    printParts(firstIndex, lastIndex);
    pthread_t thread_1, thread_2;
    int newLeftIndex1 = firstIndex; int newRightIndex1 = leftIndex - 1;
    int newLeftIndex2 = leftIndex +1; int newRightIndex2 = lastIndex;
    int indexes1[2] = {newLeftIndex1, newRightIndex1};
    int indexes2[2] = {newLeftIndex2, newRightIndex2};
    if (newLeftIndex1 < newRightIndex1)
        pthread_create(&thread_1, NULL, (void *)sort, indexes1);
    if (newLeftIndex2 < newRightIndex2)
        pthread_create(&thread_2, NULL, (void *)sort, indexes2);
    if (newLeftIndex1 < newRightIndex1)
        pthread_join(thread_1, NULL);
    if (newLeftIndex2 < newRightIndex2)
        pthread_join(thread_2, NULL);    
}

int * createRandomArray() {
    arrayOfNumbers = (int *)malloc(sizeof(int)*arraySize);
    if (arrayOfNumbers == NULL) {
        printf("Without memory");
        exit(0);
    }
    for (int index = 0; index < arraySize; index ++)
        arrayOfNumbers[index] = rand()%100;
}

void showArray() {
    for(int index = 0; index < arraySize; index++) {
        printf("%d ", arrayOfNumbers[index]);
    }
    printf("\n");
}

void printParts(int firstIndex, int lastIndex) {
    for(int index = firstIndex; index <= lastIndex; index++) {
        printf("%d ", arrayOfNumbers[index]);
    }
    printf("\n\n");
}