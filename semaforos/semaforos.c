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
void wait(pthread_t * );
void openSem(int sem_id);
void closeSem(int sem_id);

int globalVariable = 0;
int sems;

int main(int argc, char ** argv) {
    key_t semKey;
    if((semKey = ftok("/bin/ls",1) == (key_t) -1)) {
        printf("Error while creating the key\n");
        exit(1);
    }
    if( (sems = semget(semKey, 2 , IPC_CREAT|IPC_EXCL|666)) == -1) {
        printf("Error while creating the sem");
        exit(1);
    }
    if (  (semctl(sems, 0, SETVAL, 1) == -1) || (semctl(sems, 1, SETVAL, 0) == -1) ) {
        printf("Error while starting the sem");
        exit(1);
    }
    pthread_t * threadsArray = createThreadsArray();
    pthread_create(&threadsArray[0], NULL, setGlobalValue, NULL);
    pthread_create(&threadsArray[1], NULL, getGlobalValue, NULL);
    wait(threadsArray);
    return 0;
}

void wait(pthread_t * threadsArray) {
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
    for(int index = 0; index < totalTimes; index++) {
        closeSem(0);
        printf("Now the global variable has the value: %d\n" , ++globalVariable);
        openSem(1);
    }
}
void * getGlobalValue() {
    for(int index = 0; index < totalTimes; index++) {
        closeSem(1);
        printf("The current value of the variable is: %d\n" , globalVariable);
        openSem(0);
    }
}
void closeSem(int sem_id) {
    struct sembuf op;
    op.sem_num = sem_id;// Sem id
    op.sem_op = -1; // operation to do
    op.sem_flg = SEM_UNDO; // flags
    semop(sems, &op, 1);
}
void openSem(int sem_id) {
    struct sembuf op;
    op.sem_num = sem_id;// Sem id
    op.sem_op = 1; // operation to do
    op.sem_flg = SEM_UNDO; // flags
    semop(sems, &op, 1);
}
