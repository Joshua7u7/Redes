#include <stdio.h>

#ifndef udp_server
#define udp_server

#define IP "127.0.0.1"
#define ERROR -1
#define BUFFER_TAM 1024
#define TRUE 1

typedef struct {
    int descriptor;
    struct sockaddr_in address;
}client_info;

typedef client_info * client_data;

int PORT =  80821;


void CreateSocket(int * );
struct sockaddr_in  MakeBind(int *, struct sockaddr_in );
void reciveFrom(int , struct sockaddr_in);
void handle_client(client_data);

#endif