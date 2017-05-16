#include "../../include/data/dynamic_parametres.h"
#include <stdio.h>


void create_dynamic_parametres(Dynamic_parametres* dynamic_parametres)
{
    dynamic_parametres->members[0][1] ="Used_Memory" ;
    dynamic_parametres->members[0][0] = get_method_value_by_array(USED_MEMORY,30);
    dynamic_parametres->members[1][1] ="STB_ethernet_Port_Status" ;
    dynamic_parametres->members[1][0] = get_method_value_by_array(STB_ETHERNET_PORT_STATUS,20);
    dynamic_parametres->members[2][1] ="HDMI_port_Status" ;
    dynamic_parametres->members[2][0] =get_method_value_by_array(HDMI_PORT_STATUS,MAX_MW_PARAM_SIZE);
	dynamic_parametres->members[3][1] ="TotalSoftwareUpdates";
	dynamic_parametres->members[3][0] =get_method_value_by_array(TOTAL_SOFTWARE_UPDATES,50);
    dynamic_parametres->members[4][1] ="Internal_Temperature" ;
    dynamic_parametres->members[4][0] =get_method_value_by_array(INTERNAL_TEMPERATURE,11);
    dynamic_parametres->members[5][1] ="CPU_Utilisation" ;
    dynamic_parametres->members[5][0] =get_method_value_by_array(CPU_UTILISATION,30);
}
