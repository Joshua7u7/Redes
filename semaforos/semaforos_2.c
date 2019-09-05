#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>


#define totalThreads 2
#define totalTimes 5
#define totalSems 1
#define numberOfProductions 10
#define totalSections 2

pthread_t * createThreadsArray();
void * setGlobalValue();
void * getGlobalValue();
void wait(pthread_t * );
void openSem(int sem_id);
void closeSem(int sem_id);

int globalVariable = 0;
int sems;
char critic_section[totalSections][12];

int main(int argc, char ** argv) {
    key_t semKey;
    pthread_t * threadsArray = createThreadsArray();
    if((semKey = ftok("/bin/ls",1) == (key_t) -1)) {
        printf("Error while creating the key\n");
        exit(1);
    }
    if( (sems = semget(semKey, totalSems , IPC_CREAT|IPC_EXCL|666)) == -1) {
        printf("Error while creating the sem\n");
        exit(1);
    }
    for (int index = 0; index < totalSems - 1; index+=2) {
        if (  (semctl(sems, index, SETVAL, 1) == -1) || (semctl(sems, index+1 , SETVAL, 0) == -1) ) {
            printf("Error while starting the sem\n");
            exit(1);
        }
    }
    for(int index = 0; index < totalThreads ; index++) {
        if (index < (totalThreads/2))
            pthread_create(&threadsArray[index], NULL, setGlobalValue, NULL);
        else
            pthread_create(&threadsArray[index], NULL, getGlobalValue, NULL);       
    }
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
    char producer[12] = "Hello world!";
    for(int index = 0; index < totalTimes; index+=2) {
        int sectionIndex = 0;
        while (1) {
            if (sectionIndex >= totalSections) sectionIndex = 0;
            if (sectionIndex < totalSections) {
                if (semctl(sems, sectionIndex, GETVAL) != 0) {
                    closeSem(index);
                    strcpy(critic_section[sectionIndex], producer);
                    printf("Se produjo la cadena %s en la sección ctítica %d\n\n", critic_section[sectionIndex], sectionIndex);
                    openSem(sectionIndex + 1);
                    break;
                }
                sectionIndex++;
                printf("Seccion %d\n", sectionIndex);
            }
        }
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
