#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "definitions.h"
   
int main(int argc, char const *argv[]) 
{ 
    int client_descriptor;
    int seconds = atoi(argv[1]);
    char * message;
    strcpy(message, argv[2]);
    CreateSocket(&client_descriptor);
    ConnectClient(client_descriptor, seconds, message);
    return 0; 
} 