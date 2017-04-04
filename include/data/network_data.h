#ifndef NETWORK_DATA_H
#define NETWORK_DATA_H
#include "get_data.h"

typedef struct Network_data{
    char* stb_subnet_mask;
    char* stb_ip_default_gateway;
    char* dns_serverII;
    char* stb_ethernet_port_status;
    char* stb_mac_ethernet;
    char* stb_ip_address;
    char* stb_mac_address;
    char* stb_serial_number;
    Get_data data;
}Network_data;

void create_network_data(Network_data *network_data);
void destroy_network_data();

#endif //NETWORK_DATA_H
