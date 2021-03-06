/**
 * 
 * 
 */ 

#ifndef THREADS_H
#define THREADS_H

typedef struct pthread_args {
    int client_socket_fd;
    struct sockaddr_in client_address;
    struct hosts_track **hosts;
} pthread_arg_t;

void *thread_client(void *args);

#endif
