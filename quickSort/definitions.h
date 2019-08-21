#include <stdio.h>
#include <stdlib.h>

#ifndef quickSort
#define quickSort

int * arrayOfNumbers;
int arraySize;

int * createRandomArray();
void showArray();
void * sort(int *);
void swap(int, int); 

#endif