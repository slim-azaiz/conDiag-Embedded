#include "data/dynamic_parametres.h"
#include <stdio.h>


void create_dynamic_parametres(Dynamic_parametres* dynamic_parametres)
{
    int i =0;
    dynamic_parametres->members[i][1] ="Used_Memory" ;
    dynamic_parametres->members[i][0] = get_method_value_by_array(USED_MEMORY,30);i++;
    dynamic_parametres->members[i][1] ="STB_ethernet_Port_Status" ;
    dynamic_parametres->members[i][0] = get_method_value_by_array(STB_ETHERNET_PORT_STATUS,20);i++;
    dynamic_parametres->members[i][1] ="HDMI_port_Status" ;
    dynamic_parametres->members[i][0] =get_method_value_by_array(HDMI_PORT_STATUS,MAX_MW_PARAM_SIZE);i++;
	dynamic_parametres->members[i][1] ="TotalSoftwareUpdates";
	dynamic_parametres->members[i][0] =get_method_value_by_array(TOTAL_SOFTWARE_UPDATES,50);i++;
    dynamic_parametres->members[i][1] ="Internal_Temperature" ;
    dynamic_parametres->members[i][0] =get_method_value_by_array(INTERNAL_TEMPERATURE,11);i++;
    dynamic_parametres->members[i][1] ="CPU_Utilisation" ;
    dynamic_parametres->members[i][0] =get_method_value_by_array(CPU_UTILISATION,30);
}
