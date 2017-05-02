#include "../../include/data/dynamic_parametres.h"
#include <stdio.h>


void create_dynamic_parametres(Dynamic_parametres* dynamic_parametres)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();

    //memoire data
    set_method(data,USED_MEMORY);
    dynamic_parametres->members[0][1] ="Usedmemory" ;
    dynamic_parametres->members[0][0] = get_method_value_by_array(get_method(data),30);
    //network data
    set_method(data,STB_ETHERNET_PORT_STATUS);
    dynamic_parametres->members[1][1] ="STB ethernet port status" ;
    dynamic_parametres->members[1][0] = get_method_value_by_array(get_method(data),20);
    set_method(data,STB_IP_ADDRESS);
    dynamic_parametres->members[2][1] ="STB ip address" ;
    dynamic_parametres->members[2][0] =get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    
    //software data
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	dynamic_parametres->members[3][1] ="Total software updates ";
	dynamic_parametres->members[3][0] =get_method_value_by_array(get_method(data),50);

    //sys_info
    set_method(data,INTERNAL_TEMPERATURE);
    dynamic_parametres->members[4][1] ="Internal Temperature" ;
    dynamic_parametres->members[4][0] =get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    dynamic_parametres->members[5][1] ="CPU Utilisation" ;
    dynamic_parametres->members[5][0] =get_method_value_by_array(get_method(data),30);
    set_method(data,HDMI_PORT_STATUS);
    dynamic_parametres->members[5][1] ="HDMI Port Status" ;
    dynamic_parametres->members[5][0] =get_method_value_by_array(get_method(data),30);
    destroy_get_data();
    free(data);
}
