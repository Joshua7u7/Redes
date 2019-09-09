#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <setjmp.h>

#ifndef semaphores
#define semaphores

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)

#define total_critic_sections 8
#define total_threads 8
#define total_files 4
#define total_messages 4
#define total_semaphores 16
#define max_string_length 50
#define closed 0
#define open 1

char messages[total_messages][max_string_length] = {
    "Ahorita vemos que pedo.", "Ay papantla, tus hijos vuelan.", "¿Qué me ve Ramírez?, ¿Qué me ve?.", "Nel, no es coca, es harina."};

char filenames[total_files][max_string_length] = {
    "./Files/file1.txt" , "./Files/file2.txt" , "./Files/file3.txt" , "./Files/file4.txt"};

char critic_section[total_critic_sections][max_string_length];
int total_productions;
int semaphores_id;
key_t semaphores_key;
int proof;


int total_consumers = 0;

void writeMessageInFile(char * , char * );
void initializeFiles();
pthread_t * createThreads();
void setKey();
void createSemaphores();
void initializeSemaphores();
void showSemaphoresValues();
void openSemaphore(int, int);
void closeSemaphore(int, int);
void * setGlobalValue(void *);
void * getGlobalValue();
void wait(pthread_t * );
void setValueOnFile(char * );

#endif