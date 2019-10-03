#include <stdio.h>

#ifndef server
#define server

#define ERROR -1
#define PORT 8081
#define totalClients 1
#define BUFFER_TAM 1024
#define LOCALHOST "10.100.69.253"
// #define CLIENTSERVER "10.100.76.126"
#define CLIENTSERVER "10.100.69.253"
#define BLOCKING 1
#define NOTBLOCKING 2

void CreateSocket(int * );
void MakeBind(int * );
void Listen(int , int);
void AcceptNotBlocking(struct sockaddr_in  , int , int );
void AcceptBlocking(struct sockaddr_in  , int , int );
struct sockaddr_in InetPton();
void ConnectClient(int);
void * handleConnections(void *);
void initializeFile();

#endif