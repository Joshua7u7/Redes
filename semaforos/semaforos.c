#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define totalThreads 2
#define totalTimes 50

pthread_t * createThreadsArray();
void * setGlobalValue();
void * getGlobalValue();
void wait(pthread_t ** );

int globalVariable = 0;

int main(int argc, char ** argv) {
    pthread_t * threadsArray = createThreadsArray();
    pthread_create(&threadsArray[0], NULL, setGlobalValue, NULL);
    pthread_create(&threadsArray[1], NULL, getGlobalValue, NULL);
    wait(&threadsArray);
    return 0;
}

void wait(pthread_t ** threadsArray) {
    for(int index = 0; index < totalThreads; index++) {
        pthread_join(threadsArray[index], NULL);
    }
}
pthread_t * createThreadsArray() {
    pthread_t * array = (pthread_t *)malloc( sizeof(pthread_t) * totalThreads );
    if(array == NULL) {
        printf("No enought memory, sorry");
        exit(0);
    }
    return array;
}

void * setGlobalValue() {
    for(int index = 0; index < totalTimes; index++) 
        printf("Now the global variable has the value: %d\n" , ++globalVariable);
}

void * getGlobalValue() {
    for(int index = 0; index < totalTimes; index++) 
        printf("The current value of the variable is: %d\n" , globalVariable);
}
