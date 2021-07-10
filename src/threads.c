/**
 * 
 * 
 */

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_ntop
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "comm_s.h"
#include "threads.h"
#include "config.h"
#include "iputils.h"
#include "utils.h"
#include "comm.h"

void *thread_client(void *args)
{
    pthread_arg_t *pthread_args = (pthread_arg_t *)args;
    int client_socket_fd = pthread_args->client_socket_fd;   
    //struct sockaddr_in client_address = pthread_args->client_address;
    //struct in_addr client_sin_addr = client_address.sin_addr;

   
    //printf("Client Address %d", inet_ntop(client_sin_addr.s_addr));
    struct hosts_track *host = pthread_args->hosts[0];
    //printf("host id es :*%s*\n", host->Id);
    //strcpy(host->Id, "test");
    //get_ipv4(&client_address, host->Ip);
    //printf("host Ip es :*%s*\n", host->Ip);

    printf("Client connected\n\r");
    fflush(stdout);

    struct MonnetHeader *recive_head = malloc(sizeof(struct MonnetHeader));
    char *recive_payload = NULL;

    if (receive_msg(client_socket_fd, &recive_head, &recive_payload)) {
        printf("Msg main: %s\n", recive_head->msg);
        printf("Payload main:%s\n", recive_payload);
        if(strcmp(recive_head->msg, "HELLO") == 0) {
            /* 
            Comprobar si ip o id existe
            si no existe pillar hueco
            enviar error o sobreescribir
            ¿que pasa si se desconecta el cliente y envia otra vez el hello?

            */
            //printf("Es hello\n");

        }
    }
    
    free(recive_head);
    free(recive_payload);
    free(args);
    printf("Client Socket closed\n\r");
    fflush(stdout);
    close(client_socket_fd);
    pthread_exit(NULL);
}
