#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include "definitions.h"

int PORT = 8081;

void CreateSocket(int * descriptor) {
    if ( (*descriptor = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR ) {
        perror("\nError while creating the socket\n");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in InetPton() {
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) { 
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE); 
    }
    return serv_addr;
}

void ConnectClient(int descriptor) {
    struct sockaddr_in serv_addr = InetPton();
    char * message = (char*)malloc(sizeof(char)* BUFFER_TAM);
    char *server_response = (char*)calloc(sizeof(char), BUFFER_TAM);
    if (connect(descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
        printf("Type the message: ");
        scanf("%[^\n]", message);
        send(descriptor , message , strlen(message) , 0 );
        if (recv( descriptor , server_response, BUFFER_TAM, 0) < 0)
            printf("[-]Error in receiving data.\n");
        else {
            printf("\n The server change my port to %s\n", server_response );
            change_port(server_response, serv_addr, descriptor);
        }
}

void change_port(char * port, struct sockaddr_in server_address, int descriptor) {
    
    char * message = (char*)malloc(sizeof(char)* BUFFER_TAM);
    char *server_response = (char*)calloc(sizeof(char), BUFFER_TAM);
    server_address.sin_port = htons(atoi(port));

    if (connect(descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 ) {
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    while(TRUE) {
        printf("Type the message: ");
        scanf("%[^\n]", message);
        getchar();
        send(descriptor , message , strlen(message) , 0 );
        if (recv( descriptor , server_response, BUFFER_TAM, 0) < 0)
            printf("[-]Error in receiving data.\n");
        else
            printf("\n The server response is: %s\n", server_response );
    }
}