#include <stdio.h>


#include "get_data.h"

typedef struct Dynamic_parametres 
{
    Get_data data;
    //conditional_access
	char* used_memory ;
    char* stb_ethernet_port_status;
    char* stb_ip_address;
    char* total_software_updates;
    char* Internal_Temperature;
    char* CPU_Utilisation;
    char* HDMI_Port_Status;
}Dynamic_parametres; 


void create_dynamic_parametres(Dynamic_parametres *dynamic_parametres);
