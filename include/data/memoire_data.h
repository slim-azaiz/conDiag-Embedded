#ifndef MEMOIRE_DATA_H
#define MEMOIRE_DATA_H
#include "get_data.h"

typedef struct Memoire_data
{
	char* addressing_memory;
	char* memory_block_status;
	char* used_memory ;
	char* total_memory;
}Memoire_data;

void create_Memoire_data(Memoire_data* memoire_data);
void destroy_Memoire_data();

#endif // MEMOIRE_DATA_H
