#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "definitions.h"

int petitions_counter = 0;

void CreateSocket(int * descriptor) {
    if ( (*descriptor = socket(AF_INET, SOCK_STREAM, 0)) == ERROR ) {
        perror("\nError while creating the socket\n");
        exit(EXIT_FAILURE);
    }
}

void MakeBind(int * descriptor) {
    struct sockaddr_in address;
    int opt = 1;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if( setsockopt(*descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("\nSetsockopt\n");
        exit(EXIT_FAILURE);
    }
    if ( bind(*descriptor, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror("\nError while making the bind\n");
        exit(EXIT_FAILURE);
    }
}

void Listen(int descriptor) {
    if (listen(descriptor, totalClients) < 0) {
        perror("\nError while listening\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSocket listening in port %d\n", PORT);
}

void Accept(struct sockaddr_in  address, int descriptor, int struct_len) {
    int comunication_chanel_descriptor;
    char * response = "Hello from server";
    char buffer[BUFFER_TAM];
    while (1) {
        if ( (comunication_chanel_descriptor = accept(descriptor, (struct sockaddr *)&address, (socklen_t*)&struct_len)) < 0) {
        perror("\nError in accept\n");
        exit(EXIT_FAILURE);
        }
        int valread = read(comunication_chanel_descriptor, buffer, BUFFER_TAM);
        printf("\n I got %s\n", buffer);
        if (++petitions_counter == 2) {
            send(comunication_chanel_descriptor, response, strlen(response), 0);
            petitions_counter = 0;
        }
    }
}

