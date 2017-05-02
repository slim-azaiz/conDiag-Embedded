#include "../../include/data/all_parametres.h"
#include <stdio.h>


void create_all_parametres(All_parametres* all_parametres)
{

   // members = (char *)malloc(40 * 2 * sizeof(char*));
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
    //stb identification   
    set_method(data,SERIAL_NUMBER);
	all_parametres->members[0][1]= "serial number" ;
	all_parametres->members[0][0]= get_method_value_by_array(get_method(data),30);
	set_method(data,NAGRA_SERIAL_NUMBER);
	all_parametres->members[1][1]= "Nagra serial number" ;
	all_parametres->members[1][0]= get_method_value_by_array(get_method(data),30);
	set_method(data,MODEL);
	all_parametres->members[2][1]= "Model" ;
	all_parametres->members[2][0]= get_method_value_by_array(get_method(data),20);
	set_method(data,STB_MAC_ADDRESS);
	all_parametres->members[3][1]="STB mac address" ;
	all_parametres->members[3][0]= get_method_value_by_array(get_method(data),20);
	set_method(data,ETHERNET_MAC_ADDRESS);
	all_parametres->members[4][1]="Ethernet mac address" ;
	all_parametres->members[4][0]= get_method_value_by_array(get_method(data),20);
	set_method(data,FIRMWARE_VERSION);
	all_parametres->members[5][1]="Firmware version" ;
	all_parametres->members[5][0]= get_method_value_by_array(get_method(data),40);
	set_method(data,STB_MANUFACTURING_DATE);
	all_parametres->members[6][1]="STB manufacturing date" ;
	all_parametres->members[6][0]= get_method_value_by_array(get_method(data),30);
	set_method(data,HARDWARE_VERSION);
	all_parametres->members[7][1]="Hardware version";
	all_parametres->members[7][0]= get_method_value_by_array(get_method(data),10);
	set_method(data,NETWORK_ID);
	all_parametres->members[8][1]="Network id" ;
	all_parametres->members[8][0]= get_method_value_by_array(get_method(data),50);
	set_method(data,MANUFACTURER);
	all_parametres->members[9][1]="Manufacturer" ;	
	all_parametres->members[9][0]= get_method_value_by_array(get_method(data),26);	



    //conditional access
    set_method(data,NAGRA_SERIAL_NUMBER);
    all_parametres->members[10][1]="Nagra Serial Number" ;
    all_parametres->members[10][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,CA_PROVIDER_NAME);
    all_parametres->members[11][1]="CA Provider Name" ;
    all_parametres->members[11][0]= get_method_value_by_array(get_method(data),20);
    
    //loader data
    set_method(data,BOOT_LOADER_CRC);
    all_parametres->members[12][1]="Boot loader crc" ;
    all_parametres->members[12][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,BOOTLOADER_VERSION);
    all_parametres->members[13][1]="Boot loader version" ;
    all_parametres->members[13][0]= get_method_value_by_array(get_method(data),5);
   
    //memoire data
    set_method(data,ADDRESSING_MEMORY);
    all_parametres->members[14][1]="Addressing memory" ;
    all_parametres->members[14][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,MEMORY_BLOCK_STATUS);
    all_parametres->members[15][1]="Memory block status" ;
    all_parametres->members[15][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,USED_MEMORY);
    all_parametres->members[16][1]="Used memory" ;
    all_parametres->members[16][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,TOTAL_MEMORY);
    all_parametres->members[17][1]="Total memory" ;
    all_parametres->members[17][0]= get_method_value_by_array(get_method(data),30);
    
    //network data
	set_method(data,SERIAL_NUMBER);
    all_parametres->members[18][1]="STB serial number" ;
    all_parametres->members[18][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_SUBNET_MASK);
    all_parametres->members[19][1]="STB subnet mask" ;
    all_parametres->members[19][0]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    set_method(data,STB_IP_DEFAULT_GATEWAY);
    all_parametres->members[20][1]="STB ip default_gateway" ;
    all_parametres->members[20][0]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
	set_method(data,STB_MAC_ADDRESS);
    all_parametres->members[21][1]="STB mac address" ;   
    all_parametres->members[21][0]= get_method_value_by_array(get_method(data),20);   
	set_method(data,DNS_SERVER_II);
    all_parametres->members[22][1]="dns serverII" ;
    all_parametres->members[22][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_ETHERNET_PORT_STATUS);//TBD without gather
    all_parametres->members[23][1]="STB ethernet port_status" ;
    all_parametres->members[23][0]= get_method_value_by_array(get_method(data),20);
    set_method(data,ETHERNET_MAC_ADDRESS);
    all_parametres->members[24][1]="STB mac ethernet" ; 
    all_parametres->members[24][0]= get_method_value_by_array(get_method(data),20); 
    set_method(data,STB_IP_ADDRESS);
    all_parametres->members[25][1]="STB ip address" ;
    all_parametres->members[25][0]= get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    
    //software data
	set_method(data,BOOTLOADER_VERSION);
	all_parametres->members[26][1]="Boot loader version" ;
	all_parametres->members[26][0]= get_method_value_by_array(get_method(data),5);
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	all_parametres->members[27][1]="Total software updates" ;
	all_parametres->members[27][0]= get_method_value_by_array(get_method(data),50);
	set_method(data,DATE_TIME_LAST_STB_SOFTWARE);
	all_parametres->members[28][1]="Date time last stb software";
	all_parametres->members[28][0]= get_method_value_by_array(get_method(data),30);
	set_method(data,TIVO_SOFTWARE_NAME);
	all_parametres->members[29][1]="TiVo software name";
	all_parametres->members[29][0]= get_method_value_by_array(get_method(data),40);

    //sys_info
    set_method(data,IR_INPUT_STATUS);
    all_parametres->members[30][1]="IR Input Status" ;
    all_parametres->members[30][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,INTERNAL_TEMPERATURE);
    all_parametres->members[31][1]="Internal Temperature" ;
    all_parametres->members[31][0]= get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    all_parametres->members[32][1]="CPU Utilisation" ;
    all_parametres->members[32][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,HDMI_PORT_STATUS);
    all_parametres->members[33][1]="HDMI Port Status" ;
    all_parametres->members[33][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_RESOLUTION);
    all_parametres->members[34][1]="Video Resolution" ;
    all_parametres->members[34][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_ASPECT_RATIO);
    all_parametres->members[35][1]="Video Aspect_Ratio" ;
    all_parametres->members[35][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_FORMAT);
    all_parametres->members[36][1]="Video Format" ;
    all_parametres->members[36][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,DIAGNOSTICS_PAGES_LANGUAGE);
    all_parametres->members[37][1]="Diagnostics Pages Language" ;
    all_parametres->members[37][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,AUDIO_SETUP);
    all_parametres->members[38][1]="Audio Setup" ;
    all_parametres->members[38][0]= get_method_value_by_array(get_method(data),30);
    set_method(data,STB_LIFE_TIME);
    all_parametres->members[39][1]="STB Lifetime" ;   
    all_parametres->members[39][0]= get_method_value_by_array(get_method(data),50);   
    set_method(data,TOTAL_STB_POWER_OFF);
    all_parametres->members[40][1]="STB total Power Off" ;   
    all_parametres->members[40][0]= get_method_value_by_array(get_method(data),50);   
    set_method(data,TIME_SINCE_LAST_STB_BOOT_UP);
    all_parametres->members[41][1]="Time since last STB boot up" ;  
    all_parametres->members[41][0]= get_method_value_by_array(get_method(data),50);  
    set_method(data,TOTAL_STB_REBOOT);
    all_parametres->members[42][1]= "Total STB Reboot" ;
    all_parametres->members[42][0]= get_method_value_by_array(get_method(data),50);
    
    destroy_get_data();
    free(data);
}
