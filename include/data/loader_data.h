#ifndef LOADER_DATA_H
#define LOADER_DATA_H
#include "get_data.h"

typedef struct Loader_data{
    char* boot_loader_version;
    char* boot_loader_crc;
}Loader_data;

void create_Loader_datap(Loader_data * Loader_data);
void destroy_Loader_data();


#endif // LOADER_DATA_H
