#ifndef SOFTWARE_DATA_H
#define SOFTWARE_DATA_H

#include "get_data.h"

typedef struct  Software_data {

	char* bootloader_version;
    char* tivo_software_name;
    char* date_time_last_stb_software;
    char* total_software_updates;
}Software_data;


void create_software_data(Software_data *software_data);
void destroy_software_data();
#endif //SOFTWARE_DATA_H
