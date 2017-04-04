#include "../../include/data/stb_identification_data.h"
#include <stdio.h>

void destroy_Stb_identification_data()
{
	
}

void create_Stb_identification_data(Stb_identification_data* stb_identification_data)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
   
    set_method(data,SERIAL_NUMBER);
	stb_identification_data->serial_number = get_method_value_by_array(get_method(data),30);
	set_method(data,NAGRA_SERIAL_NUMBER);
	stb_identification_data->nagra_serial_number = get_method_value_by_array(get_method(data),30);
	set_method(data,MODEL);
	stb_identification_data->model = get_method_value_by_string(get_method(data));
	set_method(data,STB_MAC_ADDRESS);
	stb_identification_data->stb_mac_address = get_method_value_by_array(get_method(data),20);
	set_method(data,ETHERNET_MAC_ADDRESS);
	stb_identification_data->ethernet_mac_address = get_method_value_by_array(get_method(data),20);
	set_method(data,FIRMWARE_VERSION);
	stb_identification_data->firmware_version = get_method_value_by_array(get_method(data),40);
	set_method(data,STB_MANUFACTURING_DATE);
	stb_identification_data->stb_manufacturing_date = get_method_value_by_string(get_method(data));
	set_method(data,HARDWARE_VERSION);
	stb_identification_data->hardware_version = get_method_value_by_array(get_method(data),10);
	set_method(data,NETWORK_ID);
	stb_identification_data->network_id = get_method_value_by_array(get_method(data),50);
	set_method(data,MANUFACTURER);
	stb_identification_data->manufacturer = get_method_value_by_array(get_method(data),26);	

    destroy_get_data();
    free(data);
}
