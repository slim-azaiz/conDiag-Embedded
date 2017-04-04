#include "../../include/data/network_data.h"
#include <stdio.h>

void destroy_network_data()
{
	
}

void create_network_data(Network_data* network_data)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();

	set_method(data,SERIAL_NUMBER);
    network_data->stb_serial_number = get_method_value_by_array(get_method(data),30);
    set_method(data,STB_SUBNET_MASK);
    network_data->stb_subnet_mask = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    set_method(data,STB_IP_DEFAULT_GATEWAY);
    network_data->stb_ip_default_gateway = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
	set_method(data,STB_MAC_ADDRESS);
    network_data->stb_mac_address = get_method_value_by_array(get_method(data),20);   
	set_method(data,DNS_SERVER_II);
    network_data->dns_serverII = get_method_value_by_string(get_method(data));
    set_method(data,STB_ETHERNET_PORT_STATUS);//TBD without gather
    network_data->stb_ethernet_port_status = get_method_value_by_string(get_method(data));
    set_method(data,ETHERNET_MAC_ADDRESS);
    network_data->stb_mac_ethernet = get_method_value_by_array(get_method(data),20); 
    set_method(data,STB_IP_ADDRESS);
    network_data->stb_ip_address = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);

    destroy_get_data();
    free(data);
}
