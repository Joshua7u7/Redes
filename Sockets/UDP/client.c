#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "definitions.h"
   
int main(int argc, char const *argv[]) 
{ 
    int client_descriptor;
    CreateSocket(&client_descriptor);
    ConnectClient(client_descriptor);
    return 0; 
} 