#include "../../include/data/all_parametres.h"
#include <stdio.h>


void create_all_parametres(All_parametres* all_parametres)
{

   // members = (char *)malloc(40 * 2 * sizeof(char*));
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
    //stb identification   
    set_method(data,SERIAL_NUMBER);
	all_parametres->members[0][0]= "serial_number" ;
	all_parametres->members[0][1]= get_method_value_by_array(get_method(data),30);
	set_method(data,NAGRA_SERIAL_NUMBER);
	all_parametres->members[1][0]= "nagra_serial_number" ;
	all_parametres->members[1][1]= get_method_value_by_array(get_method(data),30);
	set_method(data,MODEL);
	all_parametres->members[2][0]= "model" ;
	all_parametres->members[2][1]= get_method_value_by_array(get_method(data),20);
	set_method(data,STB_MAC_ADDRESS);
	all_parametres->members[3][0]="stb_mac_address" ;
	all_parametres->members[3][1]= get_method_value_by_array(get_method(data),20);
	set_method(data,ETHERNET_MAC_ADDRESS);
	all_parametres->members[4][0]="ethernet_mac_address" ;
	all_parametres->members[4][1]= get_method_value_by_array(get_method(data),20);
	set_method(data,FIRMWARE_VERSION);
	all_parametres->members[5][0]="firmware_version" ;
	all_parametres->members[5][1]= get_method_value_by_array(get_method(data),40);
	set_method(data,STB_MANUFACTURING_DATE);
	all_parametres->members[6][0]="stb_manufacturing_date" ;
	all_parametres->members[6][1]= get_method_value_by_array(get_method(data),30);
	set_method(data,HARDWARE_VERSION);
	all_parametres->members[7][0]="hardware_version";
	all_parametres->members[7][1]= get_method_value_by_array(get_method(data),10);
	set_method(data,NETWORK_ID);
	all_parametres->members[8][0]="network_id" ;
	all_parametres->members[8][1]= get_method_value_by_array(get_method(data),50);
	set_method(data,MANUFACTURER);
	all_parametres->members[9][0]="manufacturer" ;	
	all_parametres->members[9][1]= get_method_value_by_array(get_method(data),26);	



    //conditional access
    set_method(data,NAGRA_SERIAL_NUMBER);
    all_parametres->members[10][0]="Nagra_Serial_Number" ;
    all_parametres->members[10][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,CA_PROVIDER_NAME);
    all_parametres->members[11][0]="CA_Provider_Name" ;
    all_parametres->members[11][1]= get_method_value_by_array(get_method(data),20);
    
    //loader data
    set_method(data,BOOT_LOADER_CRC);
    all_parametres->members[12][0]="boot_loader_crc" ;
    all_parametres->members[12][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,BOOTLOADER_VERSION);
    all_parametres->members[13][0]="boot_loader_version" ;
    all_parametres->members[13][1]= get_method_value_by_array(get_method(data),5);
   
    //memoire data
    set_method(data,ADDRESSING_MEMORY);
    all_parametres->members[14][0]="addressing_memory" ;
    all_parametres->members[14][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,MEMORY_BLOCK_STATUS);
    all_parametres->members[15][0]="memory_block_status" ;
    all_parametres->members[15][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,USED_MEMORY);
    all_parametres->members[16][0]="used_memory" ;
    all_parametres->members[16][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,TOTAL_MEMORY);
    all_parametres->members[17][0]="total_memory" ;
    all_parametres->members[17][1]= get_method_value_by_array(get_method(data),30);
    
    //network data
	set_method(data,SERIAL_NUMBER);
    all_parametres->members[18][0]="stb_serial_number" ;
    all_parametres->members[18][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_SUBNET_MASK);
    all_parametres->members[19][0]="stb_subnet_mask" ;
    all_parametres->members[19][1]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    set_method(data,STB_IP_DEFAULT_GATEWAY);
    all_parametres->members[20][0]="stb_ip_default_gateway" ;
    all_parametres->members[20][1]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
	set_method(data,STB_MAC_ADDRESS);
    all_parametres->members[21][0]="stb_mac_address" ;   
    all_parametres->members[21][1]= get_method_value_by_array(get_method(data),20);   
	set_method(data,DNS_SERVER_II);
    all_parametres->members[22][0]="dns_serverII" ;
    all_parametres->members[22][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_ETHERNET_PORT_STATUS);//TBD without gather
    all_parametres->members[23][0]="stb_ethernet_port_status" ;
    all_parametres->members[23][1]= get_method_value_by_array(get_method(data),20);
    set_method(data,ETHERNET_MAC_ADDRESS);
    all_parametres->members[24][0]="stb_mac_ethernet" ; 
    all_parametres->members[24][1]= get_method_value_by_array(get_method(data),20); 
    set_method(data,STB_IP_ADDRESS);
    all_parametres->members[25][0]="stb_ip_address" ;
    all_parametres->members[25][1]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    
    //software data
	set_method(data,BOOTLOADER_VERSION);
	all_parametres->members[26][0]="boot_loader_version" ;
	all_parametres->members[26][1]= get_method_value_by_array(get_method(data),5);
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	all_parametres->members[27][0]="total_software_updates" ;
	all_parametres->members[27][1]= get_method_value_by_array(get_method(data),50);
	set_method(data,DATE_TIME_LAST_STB_SOFTWARE);
	all_parametres->members[28][0]="date_time_last_stb_software";
	all_parametres->members[28][1]= get_method_value_by_array(get_method(data),30);
	set_method(data,TIVO_SOFTWARE_NAME);
	all_parametres->members[29][0]="tivo_software_name";
	all_parametres->members[29][1]= get_method_value_by_array(get_method(data),40);

    //sys_info
    set_method(data,IR_INPUT_STATUS);
    all_parametres->members[30][0]="IR_Input_Status" ;
    all_parametres->members[30][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,INTERNAL_TEMPERATURE);
    all_parametres->members[31][0]="Internal_Temperature" ;
    all_parametres->members[31][1]= get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    all_parametres->members[32][0]="CPU_Utilisation" ;
    all_parametres->members[32][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,HDMI_PORT_STATUS);
    all_parametres->members[33][0]="HDMI_Port_Status" ;
    all_parametres->members[33][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_RESOLUTION);
    all_parametres->members[34][0]="Video_Resolution" ;
    all_parametres->members[34][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_ASPECT_RATIO);
    all_parametres->members[35][0]="Video_Aspect_Ratio" ;
    all_parametres->members[35][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_FORMAT);
    all_parametres->members[36][0]="Video_Format" ;
    all_parametres->members[36][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,DIAGNOSTICS_PAGES_LANGUAGE);
    all_parametres->members[37][0]="Diagnostics_Pages_Language" ;
    all_parametres->members[37][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,AUDIO_SETUP);
    all_parametres->members[38][0]="Audio_Setup" ;
    all_parametres->members[38][1]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_LIFE_TIME);
    all_parametres->members[39][0]="STB_Lifetime" ;   
    all_parametres->members[39][1]= get_method_value_by_array(get_method(data),50);   
    set_method(data,TOTAL_STB_POWER_OFF);
    all_parametres->members[40][0]="STB_totalPowerOff" ;   
    all_parametres->members[40][1]= get_method_value_by_array(get_method(data),50);   
    set_method(data,TIME_SINCE_LAST_STB_BOOT_UP);
    all_parametres->members[41][0]="Time_since_last_STB_boot_up" ;  
    all_parametres->members[41][1]= get_method_value_by_array(get_method(data),50);  
    set_method(data,TOTAL_STB_REBOOT);
    all_parametres->members[42][0]= "Total_STB_Reboot" ;
    all_parametres->members[42][1]= get_method_value_by_array(get_method(data),50);
    
    destroy_get_data();
    free(data);
}
