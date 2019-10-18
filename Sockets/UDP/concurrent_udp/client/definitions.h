#include <stdio.h>

#ifndef udp_client
#define udp_client

#define IP "127.0.0.1"
#define ERROR -1
#define BUFFER_TAM 1024
#define TRUE 1



void CreateSocket(int * );
void ConnectClient(int );
void change_port(char * , struct  sockaddr_in, int );

#endif