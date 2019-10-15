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

void getData(char **);
void writeMessageInFile(char * , char * );


int client_counter = 0;

void CreateSocket(int * descriptor) {
    if ( (*descriptor = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR ) {
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

void reciveFrom(int descriptor) {
    char * buf = (char*)malloc(sizeof(char)* BUFFER_TAM);
    struct sockaddr_in address;
    char * response = "Respuesta del servidor";
    int addr_size = sizeof(address);
    while(TRUE) {
        ssize_t msg_size = recvfrom( descriptor, buf, sizeof(char)* BUFFER_TAM, 0, 
        (struct sockaddr*)&address, &addr_size);
        char * ip = inet_ntoa(address.sin_addr);
        printf("I received the message %s by %s\n", buf,ip);
        sendto( descriptor, response, sizeof(response), 0, 
        (struct sockaddr*)&address, addr_size);
    }
}

void sendTo(int descriptor) {
    char * buf = (char*)malloc(sizeof(char)* BUFFER_TAM);
    struct sockaddr_in address;
    int addr_size = sizeof(address);
    while(TRUE) {
        char * response;
        scanf("%[^\n]", response);
        sendto( descriptor, response, sizeof(response), 0, 
        (struct sockaddr*)&address, addr_size);
        ssize_t msg_size = recvfrom( descriptor, buf, sizeof(char)* BUFFER_TAM, 0, 
        (struct sockaddr*)&address, &addr_size);
        char * ip = inet_ntoa(address.sin_addr);
        printf("Server says %s by %s\n", buf,ip);
    }
}

void ConnectClient(int descriptor, int seconds, char* message) {
    struct sockaddr_in serv_addr = InetPton();
    char server_response[BUFFER_TAM] = {0};
    if (connect(descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    while(TRUE) {
        send(descriptor , message , strlen(message) , 0 );
        if (recv( descriptor , server_response, BUFFER_TAM, 0) < 0)
            printf("[-]Error in receiving data.\n");
        else
            printf("\n The server response is: %s\n", server_response );
        usleep(seconds);
    }
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
    }
    free(connection);
}

void writeMessageInFile(char * filename, char * message) {
    FILE * file = fopen(filename, "ab");
    fprintf(file, " %s \n" , message);
    fclose(file);
}

void initializeFile() {
    FILE * file = fopen("server.txt", "wb");
    fclose(file);   
}
