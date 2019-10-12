#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "definitions.h"

int main(int argc , char ** argv) {
    int server_descriptor;
    int mode = atoi(argv[1]);
    struct sockaddr_in client;
	initializeFile();
    CreateSocket(&server_descriptor);
    MakeBind(&server_descriptor);
    reciveFrom(server_descriptor);
    return 0;
}