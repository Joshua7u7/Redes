#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include "definitions.h"

/*******************************File functions************************************/
void initializeFiles() {
    for (int file = 0; file < total_files; file++) {
        FILE * currentFile = fopen(filenames[file], "wb");
        fclose( currentFile );
    }
}
void writeMessageInFile(char * filename, char * message) {
    FILE * file = fopen(filename, "ab");
    fprintf(file, "\n %s \n" , message);
    fclose(file);
}
void setValueOnFile(char * message) {
        if (strcmp(message, "Ahorita vemos que pedo.") == 0)
            writeMessageInFile(filenames[0], message);
        else if (strcmp(message, "Ay papantla, tus hijos vuelan.") == 0)
            writeMessageInFile(filenames[1], message);
        else if (strcmp(message, "¿Qué me ve Ramírez?, ¿Qué me ve?.") == 0)
            writeMessageInFile(filenames[2], message);
        else if (strcmp(message,"Nel, no es coca, es harina.") == 0)
            writeMessageInFile(filenames[3], message);
}
/*****************************End file functions*********************************/

/****************************Threads functions***********************************/
pthread_t * createThreads() {
    pthread_t * threads = (pthread_t *)malloc(sizeof(pthread_t) * total_threads);
    if ( threads == NULL) {
        printf("There's an error while creating the threads.\n");
        exit(EXIT_FAILURE);
    }
    return threads;
}
void wait(pthread_t * threads) {
    for(int current_thread = 0; current_thread < total_threads; current_thread++) {
        pthread_join(threads[current_thread], NULL);
    }
}
void * setGlobalValue(void * current_message) {
    int productions = 0;
    int current_section = 0;
    int * number = (int *)current_message;
    while(productions < total_productions){
        if (current_section >= total_critic_sections ) current_section = 0;
		for (int current_semaphore = 0; current_semaphore < total_semaphores; current_semaphore += 2) {
			if (semctl(semaphores_id, current_semaphore, GETVAL) != 0) {
				closeSemaphore(current_semaphore, semaphores_id);
				strcpy(critic_section[current_semaphore/2], messages[*number]);
				//printf(" # Produccion '%s' en la seccion %d por %ld [%d]\n",critic_section[current_semaphore], 
                //current_semaphore, pthread_self(), ++productions);
                ++productions;
				openSemaphore(current_semaphore + 1, semaphores_id);
				break;
			}
		}
	}
}
void * getGlobalValue() {
    int current_section = 0;
    while(total_consumers < total_productions * (total_threads / 2)) {
        if (current_section >= total_critic_sections) current_section = 0;
		for (int current_semaphore = 1; current_semaphore < total_semaphores; current_semaphore += 2) {
			if(semctl(semaphores_id, current_semaphore, GETVAL) != 0){
				closeSemaphore(current_semaphore, semaphores_id);
				closeSemaphore(total_semaphores, semaphores_id); // consumos
				if(total_consumers < total_productions * (total_threads / 2)) {
                    setValueOnFile(critic_section[current_semaphore - 1]);
                    printf(" >> Consumo '%s' leído en la seccion %d por %ld [%d]\n",critic_section[current_semaphore - 1],
                    current_semaphore, pthread_self(), ++total_consumers);
                }
				openSemaphore(total_semaphores, semaphores_id);
				openSemaphore(current_semaphore - 1, semaphores_id);	
				break;
			}
		}
	}
	semctl(semaphores_id, 0, IPC_RMID, 0);
}
/**************************End threads functions*********************************/

/**************************Semaphores functions**********************************/
void setKey() {
    if ( (semaphores_key = ftok("/bin/ls", 1)) == (key_t) -1) {
        printf("Error setting the key.\n");
        exit(EXIT_FAILURE);   
    }
}
void createSemaphores() {
    printf("key = %d.\n", semaphores_key);
    if ((semaphores_id = semget(semaphores_key, total_semaphores + 1, IPC_CREAT|IPC_EXCL|666)) == -1) {
        printf("Error while creating the semaphores.\n");
        exit(EXIT_FAILURE);
    }
}
void initializeSemaphores() {
    printf("id = %d.\n", semaphores_id);
    for (int current_semaphore = 0; current_semaphore < total_semaphores; current_semaphore++) {
        int productor, consumer;
        productor = semctl(semaphores_id, current_semaphore++, SETVAL, open);
        consumer = semctl(semaphores_id, current_semaphore, SETVAL, closed);
        if( (productor == -1) || (consumer == -1) ) {
            printf("Error initializing the semaphores.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (semctl(semaphores_id,total_semaphores,SETVAL,1) == -1) {
        printf("Error initializing the semaphores.\n");
        exit(EXIT_FAILURE);
    } // contador de consumos
}
void showSemaphoresValues() {
    printf("id = %d.\n", semaphores_id);
    for (int current_semaphore = 0; current_semaphore < total_semaphores; current_semaphore++) {
       printf ("Semaphore %d has the value %d\n", current_semaphore, semctl(semaphores_id, current_semaphore, GETVAL));
    }
}
void openSemaphore(int semaphore, int sem_id) {
    struct sembuf op;
    op.sem_num = semaphore;// Sem id
    op.sem_op = 1; // operation to do
    op.sem_flg = SEM_UNDO; // flags
    semop(sem_id, &op, 1);
}
void closeSemaphore(int semaphore, int sem_id) {
    struct sembuf op;
    op.sem_num = semaphore;// Sem id
    op.sem_op = -1; // operation to do
    op.sem_flg = SEM_UNDO; // flags
    semop(sem_id, &op, 1);
}
/*************************End semaphores functions*******************************/