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
#include "threads.h"
#include "config.h"
#include "utils.h"
#include "comm.h"
#include "comm_s.h"

void *thread_client(void *args)
{
    pthread_arg_t *pthread_args = (pthread_arg_t *)args;
    int client_socket_fd = pthread_args->client_socket_fd;
    //struct sockaddr_in client_address = pthread_args->client_address;
    printf("Client connected\n\r");
    fflush(stdout);

    struct MonnetHeader *recive_head = malloc(sizeof(struct MonnetHeader));
    char *recive_payload = NULL;

    if (receive_msg(client_socket_fd, &recive_head, &recive_payload)) {
        printf("Msg main: %s\n", recive_head->msg);
        printf("Payload main:%s\n", recive_payload);
    }


    free(recive_head);
    free(args);
    //printf("Sending response %s\n", sendBuffer);
    printf("Client Socket closed\n\r");
    fflush(stdout);
    close(client_socket_fd);
    pthread_exit(NULL);
}
