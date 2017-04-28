#include <stdio.h>


#include "get_data.h"

typedef struct All_parametres 
{

    char* members[44][2];
    //stb_identification
/*    char* serial_number;
	char* nagra_serial_number;
	char* model;
	char* ethernet_mac_address;
	char* firmware_version;
	char* stb_manufacturing_date;
	char* hardware_version;
	char* network_id;
	char* manufacturer;
    Get_data data;
    //conditional_access
    char* Nagra_Serial_Number;   
    char* CA_Provider_Name;
    //loader_data
    char* boot_loader_version;
    char* boot_loader_crc;
    //memoire_data
	char* addressing_memory;
	char* memory_block_status;
	char* used_memory ;
	char* total_memory;
    //network_data
    char* stb_subnet_mask;
    char* stb_ip_default_gateway;
    char* dns_serverII;
    char* stb_ethernet_port_status;
    char* stb_mac_ethernet;
    char* stb_ip_address;
    char* stb_mac_address;
    char* stb_serial_number;
    //software_data
    char* tivo_software_name;
    char* date_time_last_stb_software;
    char* total_software_updates;
    //sys_info
    char* IR_Input_Status;
    char* Internal_Temperature;
    char* CPU_Utilisation;
    char* HDMI_Port_Status;
    char* Video_Resolution;
    char* Video_Aspect_Ratio;
    char* Video_Format;
    char* Diagnostics_Pages_Language;
    char* Audio_Setup;
    char* STB_Lifetime;
    char* STB_totalPowerOff;
    char* Time_since_last_STB_boot_up;
	char* Total_STB_Reboot;
*/}All_parametres; 


void create_all_parametres(All_parametres *all_parametres);
