/**
 * 
 * 
 */


#ifndef COMM_S_H
#define COMM_S_H

struct Hosts {
    char Id[32];    //Trantor, Terminus
    char Os[32];  //Windows/Linux
    char OsVer[256]; //(W) 11 / (L) 5.4.0-77-generic
    char Distro[128]; // Microsoft / Ubuntu /Debian
    char Ip[128];
    size_t ncpus;
    size_t ram_memory;
    size_t shared_mem;
    size_t swap_total;
};


struct Stats {
    char Id[32];
    int load[4]; //100    
    size_t free_ram;
    size_t spaw_used; 
    size_t free_sap;
    size_t buff_mem;
    size_t procesos;
    size_t timestamp; //Timestamp
};


struct Logs {
    char Id[32];
    char log_file[32];
    char line[256];
    size_t timestamp;
};

#endif