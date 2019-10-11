#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "definitions.h"

int main(int argc , char ** argv) {
    int server_descriptor = 0;
    int mode = atoi(argv[1]);
    struct sockaddr_in client;
    if ( (mode == BLOCKING) || (mode == NOTBLOCKING) ) {
    	CreateSocket(&server_descriptor);
    	MakeBind(&server_descriptor);
    	Listen(server_descriptor, mode);
    	if (mode == BLOCKING)
    		AcceptBlocking(client, server_descriptor, sizeof(client));
    	else if( mode == NOTBLOCKING)
    		AcceptNotBlocking(client, server_descriptor, sizeof(client));
    } else
    	printf("\nSet 1 for BLOCKING and 2 for NOT BLOCKING\n");
    return 0;
}