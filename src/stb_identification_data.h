#ifndef STB_IDENTIFICATION_DATA_H
#define STB_IDENTIFICATION_DATA_H

#include "get_data.h"

struct Stb_identification_data 
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
    get_data data;
};


void create_Stb_identification_data();
void destroy_Stb_identification_data();
char* get_serial_number();
char* get_nagra_serial_number();
char* get_model();
char* get_stb_mac_address();
char* get_ethernet_mac_address();
char* get_firmware_version();
char* get_stb_manufacturing_date();
char* get_hardware_version();
char* get_network_id();
char* get_manufacturer(); 
void fetch_data();

#endif //STB_IDENTIFICATION_DATA_H
