#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "functions.c"

int main(int argc , char ** argv) {
    int server_descriptor;
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8081);
    CreateSocket(&server_descriptor);
    client = MakeBind(&server_descriptor, client);
    reciveFrom(server_descriptor, client);
    return 0;
}