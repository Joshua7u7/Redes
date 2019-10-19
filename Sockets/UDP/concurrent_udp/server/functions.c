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


void CreateSocket(int * descriptor) {
    if ( (*descriptor = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR ) {
        perror("\nError while creating the socket\n");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in MakeBind(int * descriptor, struct sockaddr_in address) {
    int opt = 1;
    if( setsockopt(*descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("\nSetsockopt\n");
        exit(EXIT_FAILURE);
    }
    if ( bind(*descriptor, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror("\nError while making the bind\n");
        exit(EXIT_FAILURE);
    }
    return address;
}

void reciveFrom(int descriptor, struct sockaddr_in address) {
    char * buf = (char*)malloc(sizeof(char)* BUFFER_TAM);
    char response[5];
    struct sockaddr_in client;
    struct sockaddr_in server_config = address;
    int addr_size = sizeof(client);
    while(TRUE) {
        ssize_t msg_size = recvfrom( descriptor, buf, sizeof(char)* BUFFER_TAM, 0, 
        (struct sockaddr*)&client, &addr_size);
        pthread_t * thread = (pthread_t*)malloc(sizeof(pthread_t));
        int new_descriptor;
        CreateSocket(&new_descriptor);
        client_data info = (client_data)malloc(sizeof(client_info));
        server_config.sin_port = htons(++PORT);
        info->descriptor = new_descriptor;
        info->address = server_config;
        pthread_create(thread ,NULL, (void *) handle_client, info);
        sprintf(response, "%d", PORT);
        sendto( descriptor, response, sizeof(response), 0, 
        (struct sockaddr*)&client, addr_size);
    }
}

void handle_client(client_data info) {
    char * buf = (char*)malloc(sizeof(char)* BUFFER_TAM);
    struct sockaddr_in client;
    int addr_size = sizeof(client);
    char * response = "Respuesta del servidor";
    int port = info->address.sin_port;
    MakeBind(&info->descriptor, info->address);
    while(TRUE) {
        ssize_t msg_size = recvfrom( info->descriptor, buf, sizeof(char)* BUFFER_TAM, 0, 
        (struct sockaddr*)&client, &addr_size);
        char * ip = inet_ntoa(client.sin_addr);
        printf("I received the message %s by %s in the port %d\n", buf,ip, port);
        sendto( info->descriptor, response, sizeof(response), 0, 
        (struct sockaddr*)&client, addr_size);
    }
}