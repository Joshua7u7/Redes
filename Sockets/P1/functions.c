#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "definitions.h"

void getData(char **);



int client_counter = 0;

void CreateSocket(int * descriptor) {
    if ( (*descriptor = socket(AF_INET, SOCK_STREAM, 0)) == ERROR ) {
        perror("\nError while creating the socket\n");
        exit(EXIT_FAILURE);
    }
}

void MakeBind(int * descriptor) {
    struct sockaddr_in address;
    int opt = 1;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if( setsockopt(*descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("\nSetsockopt\n");
        exit(EXIT_FAILURE);
    }
    if (ioctl(*descriptor, FIONBIO, (char *)&opt) < 0) {
        perror("ioctl() failed");
        exit(EXIT_FAILURE);
    }
    if ( bind(*descriptor, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror("\nError while making the bind\n");
        exit(EXIT_FAILURE);
    }
}

void Listen(int descriptor, int mode) {
    if (listen(descriptor, totalClients) < 0) {
        perror("\nError while listening\n");
        exit(EXIT_FAILURE);
    }
    if (mode == BLOCKING)
        printf("\nSocket listening in port %d on blocking mode\n", PORT);
    else
        printf("\nSocket listening in port %d on not blocking mode\n", PORT);
}

void AcceptBlocking(struct sockaddr_in  address, int descriptor, int struct_len) {
    int comunication_chanel_descriptor;
    char * response = "Hello from server";
    char buffer[BUFFER_TAM];
    bzero(buffer, sizeof(buffer));
    while (1) {
        if ( (comunication_chanel_descriptor = accept(descriptor, (struct sockaddr *)&address, (socklen_t*)&struct_len)) < 0) {
            perror("\nError in accept\n");
            exit(EXIT_FAILURE);
        }
        while( (recv(comunication_chanel_descriptor, buffer, BUFFER_TAM, 0) > 0) ) {
            printf("\n I got %s \n", buffer);
            send(comunication_chanel_descriptor, response, strlen(response), 0);
            bzero(buffer, sizeof(buffer));
        }
    }
}
void AcceptNotBlocking(struct sockaddr_in  address, int descriptor, int struct_len) {
    while(1) {
        int * comunication_chanel_descriptor = (int*)malloc(sizeof(int));
        if((*comunication_chanel_descriptor = accept(descriptor, (struct sockaddr *)&address, (socklen_t*)&struct_len)) >= 0) {
            pthread_t * new_connection = (pthread_t*)malloc(sizeof(pthread_t));
            pthread_create(new_connection, NULL, handleConnections, (void*)comunication_chanel_descriptor);
        }
    }
}

void ConnectClient(int descriptor) {
    struct sockaddr_in serv_addr = InetPton();
    char server_response[BUFFER_TAM] = {0};
<<<<<<< HEAD
    
    printf("%d", descriptor);
=======
>>>>>>> 19de3b81861180899466d5763b187942e97e34f1
    if (connect(descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    while(1) {
        char *client_message = (char *)malloc(sizeof(char) * BUFFER_TAM);
        getData(&client_message);
        if (strcmp(client_message, "@") == 0)
            break;
        send(descriptor , client_message , strlen(client_message) , 0 );
        if (recv( descriptor , server_response, BUFFER_TAM, 0) < 0)
            printf("[-]Error in receiving data.\n");
<<<<<<< HEAD
        else
            printf("\n The server response is: %s\n", server_response );
=======
        else {
            if (strcmp(server_response, "@") == 0)
                break;
            else
                printf("\n The server response is: %s\n", server_response );
        }
        bzero(server_response, sizeof(server_response));
>>>>>>> 19de3b81861180899466d5763b187942e97e34f1
    }
    close(descriptor);
}

void getData(char ** client_message) {
    fflush(stdin);
    printf("\nWrite the client message: \n");
    scanf("%[^\n]", *client_message);
    getchar();
    fflush(stdin);
}

struct sockaddr_in InetPton() {
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    if(inet_pton(AF_INET, LOCALHOST, &serv_addr.sin_addr) <= 0) { 
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE); 
    }
    return serv_addr;
}

void * handleConnections(void * connection) {
    // char * response = "Hello from server";
<<<<<<< HEAD
    char buffer[BUFFER_TAM];
    bzero(buffer, sizeof(buffer));
    int comunication_chanel_descriptor = *(int *)connection;
    while( (recv(comunication_chanel_descriptor, buffer, BUFFER_TAM, 0) > 0) ) {
        char *response = (char *)malloc(sizeof(char) * BUFFER_TAM);
        getData(&response);
        printf("%d said %s\n", comunication_chanel_descriptor, buffer);
        printf("\n Type yor response: ");
        scanf("%[^\n]", response);
        //writeMessageInFile("server.txt", buffer);
        send(comunication_chanel_descriptor, response, strlen(response), 0);
        // printf("\n I got %s \n", buffer);
        bzero(buffer, sizeof(buffer));
=======
    char * response = (char *)malloc(sizeof(char) * BUFFER_TAM);
    char buffer[BUFFER_TAM];
    bzero(buffer, sizeof(buffer));
    int comunication_chanel_descriptor = *(int *)connection;
    while(1) {
        if( (recv(comunication_chanel_descriptor, buffer, BUFFER_TAM, 0) > 0) ) {
            if (strcmp(buffer, "@") == 0)
                break;
            else {
                printf("\n %d said >> %s \n", comunication_chanel_descriptor,buffer);
                getData(&response);
                send(comunication_chanel_descriptor, response, strlen(response), 0);
                bzero(buffer, sizeof(buffer));
            }
        }
>>>>>>> 19de3b81861180899466d5763b187942e97e34f1
    }
    close(comunication_chanel_descriptor);
}