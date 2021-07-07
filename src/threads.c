/**
 * 
 * 
 */ 

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "comm.h"
#include "threads.h"
#include "utils.h"


void *thread_client(void *args)
{
    char *send_msg_buf = {0};

    pthread_arg_t *pthread_args = (pthread_arg_t *)args;
    int client_socket_fd = pthread_args->client_socket_fd;
    //struct sockaddr_in client_address = pthread_args->client_address;
    printf("Client connected\n\r");
    fflush(stdout);

    if(receive_msg(client_socket_fd)) {
        send_msg_buf = build_msg("ACK", 0, NULL);        
    } else {
        send_msg_buf = build_msg("NACK", 0, NULL);
    }
    send_msg(client_socket_fd, send_msg_buf);
    //
    free(args);
    //printf("Sending response %s\n", sendBuffer);
    printf("Client Socket closed\n\r");
    fflush(stdout);
    close(client_socket_fd);
    pthread_exit(NULL);
}
