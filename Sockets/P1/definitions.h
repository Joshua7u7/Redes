#include <stdio.h>

#ifndef server
#define server

#define ERROR -1
#define PORT 8081
#define totalClients 5
#define BUFFER_TAM 1024

void CreateSocket(int * );
void MakeBind(int * );
void Listen(int );
void Accept(struct sockaddr_in  , int , int );
#endif