#include <stdio.h>
#include <stdlib.h>

#ifndef non_blocking
#define non_blocking

#define SERVER_PORT  8081
#define TRUE 1
#define FALSE 0

int    i, len, rc, on = 1;
int    listen_sd, max_sd, new_sd;
int    desc_ready, end_server = FALSE;
int    close_conn;
char   buffer[80];
struct sockaddr_in6 addr;
struct timeval      timeout;
fd_set              master_set, working_set;

#endif