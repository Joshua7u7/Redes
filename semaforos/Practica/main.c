#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <setjmp.h>



#include "functions.c"
#include "definitions.h"

int message[] = {0,1,2,3,4};

int setProductions(char * numer_of_productions);
void showCriticSections();

int main(int argc, char ** argv) {
    pthread_t * threads = createThreads();
    total_productions = setProductions(argv[1]);
    int current_message = 0;
    setKey();
    createSemaphores();
    initializeSemaphores();
    initializeFiles();
    for(int i = 0; i < total_threads; i++, current_message++) {
        if (current_message >= total_messages) current_message = 0;  
		pthread_create(&threads[i], NULL, (void *)setGlobalValue, (void*)&message[current_message]);
		pthread_create(&threads[++i], NULL, (void *)getGlobalValue, NULL);
	}
    wait(threads);
    semctl(semaphores_id, 0, IPC_RMID, 0);
    printf("We've finished\n\n");
    return 0;
}

int setProductions(char * numer_of_productions) {
    int productions = 0;
    TRY {
        productions = atoi(numer_of_productions);      
    } CATCH {
      printf("Only numbers soported.\n");
      exit(EXIT_FAILURE);
    } ETRY;
    return productions;
}

void showCriticSections() {
    for (int i = 0; i < total_critic_sections; i++) {
        printf("MSG %d : %s \n",i+1, critic_section[i]);
    }
}