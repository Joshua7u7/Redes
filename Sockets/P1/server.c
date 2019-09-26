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
    struct sockaddr_in client;
    CreateSocket(&server_descriptor);
    MakeBind(&server_descriptor);
    Listen(server_descriptor);
    Accept(client, server_descriptor, sizeof(client));
    return 0;
}