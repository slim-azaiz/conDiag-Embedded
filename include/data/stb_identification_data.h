#ifndef STB_IDENTIFICATION_DATA_H
#define STB_IDENTIFICATION_DATA_H

#include "get_data.h"

typedef struct Stb_identification_data 
{
    char* serial_number;
	char* nagra_serial_number;
	char* model;
	char* stb_mac_address;
	char* ethernet_mac_address;
	char* firmware_version;
	char* stb_manufacturing_date;
	char* hardware_version;
	char* network_id;
	char* manufacturer;
    Get_data data;
}Stb_identification_data; 


void create_Stb_identification_data(Stb_identification_data *stb_identification_data);
void destroy_Stb_identification_data();

#endif //STB_IDENTIFICATION_DATA_H
