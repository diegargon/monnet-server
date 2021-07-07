/**
 * 
 * 
 */

#ifndef COMM_H
#define COMM_H

char *build_msg(char *msg, int ack, char *payload);
bool send_msg(int socket_fd, char* msg);
bool receive_msg(int socket_fd);

#endif
