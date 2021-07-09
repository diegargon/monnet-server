/**
 * 
 * 
 */ 

#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "main.h"
#include "threads.h"
#include "signals.h"

void error_warning(char *msg) {
    perror(msg);
}

void error_fatal(char* msg){
    perror(msg);
    fflush(stdout);
    exit(1);
}

int main(int argc, char *argv[]) {
    int socket_fd, client_socket_fd;    
    int port = PORT;
    struct sockaddr_in address;
    socklen_t client_address_len;
    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_args;
    pthread_t pthread;

    /* Signals */
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGINT, signal_handler);

    /* Fill IPv4 struct */ 
    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_fatal("socket");
    }

    /*  Bind TCP Socket */
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof address) == -1) {
        error_fatal("bind");
    }

    /* Socket  Listening */
    /* SOMAXCONN Auto max conn queue */
    if (listen(socket_fd, SOMAXCONN) == -1) {
        error_fatal("listen");        
    }    

    /* Init threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        error_fatal("pthread_attr_init");
        
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        error_fatal("pthread_attr_setdetachstate");
    }    

    while(1) {
       pthread_args = (pthread_arg_t *)malloc(sizeof *pthread_args);
        if (!pthread_args) {
            error_warning("malloc");
            continue;
        }

        client_address_len = sizeof pthread_args->client_address;
        printf("Server is accepting connections\n");
        client_socket_fd = accept(socket_fd, (struct sockaddr *)&pthread_args->client_address, &client_address_len);
        if (client_socket_fd == -1) {
            error_warning("accept");
            free(pthread_args);
            continue;
        }

        pthread_args->client_socket_fd = client_socket_fd;        
        if (pthread_create(&pthread, &pthread_attr, thread_client, (void *)pthread_args) != 0) {
            error_warning("pthread_create");
            free(pthread_args);
            continue;
        }
        
    }

    //close(socket_fd); //NEVER

    return 0;    
}
