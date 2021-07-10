/**
 * 
 * 
 */

#include <arpa/inet.h> //inet_ntop
#include <string.h>

void get_ipv4(struct sockaddr_in *address, char *ip)
{
    inet_ntop( AF_INET, &address->sin_addr, ip, INET6_ADDRSTRLEN);
}