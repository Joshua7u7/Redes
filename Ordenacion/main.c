#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "definitions.h"
#include "functions.c"

void verifyInputs(int, char **);

int main(int argc, char ** argv) {
    verifyInputs(argc, argv);
    arraySize = atoi(argv[1]);
    int firstIndexes[2] = {0, arraySize -1};
    createRandomArray();
    printf("\n\nInitial array: \n\n");
    showArray();
    sort(firstIndexes);
    printf("\n\nFinal array: \n\n");
    showArray();
    printf("\n");
}

void verifyInputs(int totalArguments, char ** arguments) {
    if(totalArguments < 2) {
        printf("You miss arguments");
        exit(0);
    }
}