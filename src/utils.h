/**
 * 
 * 
 */

#ifndef UTILS_H
#define UTILS_H

struct MonnetHeader
{
    int version;
    int ack;
    char auth[32];
    char msg[32];
    size_t size;
};

char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
size_t get_payload_size(char *buf);
struct MonnetHeader get_header(char *header);

#endif
