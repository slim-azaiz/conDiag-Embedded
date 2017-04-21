#include "../../include/data/dynamic_parametres.h"
#include <stdio.h>


void create_dynamic_parametres(Dynamic_parametres* dynamic_parametres)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();

    //memoire data
    set_method(data,USED_MEMORY);
    dynamic_parametres->used_memory = get_method_value_by_array(get_method(data),30);
    //network data
    set_method(data,STB_ETHERNET_PORT_STATUS);
    dynamic_parametres->stb_ethernet_port_status = get_method_value_by_array(get_method(data),20);
    set_method(data,STB_IP_ADDRESS);
    dynamic_parametres->stb_ip_address = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    
    //software data
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	dynamic_parametres->total_software_updates = get_method_value_by_array(get_method(data),50);

    //sys_info
    set_method(data,INTERNAL_TEMPERATURE);
    dynamic_parametres->Internal_Temperature = get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    dynamic_parametres->CPU_Utilisation = get_method_value_by_array(get_method(data),30);
    set_method(data,HDMI_PORT_STATUS);
    dynamic_parametres->HDMI_Port_Status = get_method_value_by_array(get_method(data),30);
    destroy_get_data();
    free(data);
}
