#include <stdio.h>

#ifndef server
#define server

#define ERROR -1
#define PORT 8081
#define totalClients 2
#define BUFFER_TAM 1024
#define LOCALHOST "127.0.0.1"
#define BLOCKING 1
#define NOTBLOCKING 2
#define MINUTES 3
#define SECONDS 60
#define TRUE 1
#define FALSE 0

void CreateSocket(int * );
void MakeNoBlocking(int );
void MakeBind(int * );
void Listen(int , int);
void AcceptNotBlocking(struct sockaddr_in  , int , int );
void AcceptBlocking(struct sockaddr_in  , int , int );
struct sockaddr_in InetPton();
void ConnectClient(int);
void * handleConnections(void *);
#endif