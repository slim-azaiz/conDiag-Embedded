#include "../../include/data/all_parametres.h"
#include <stdio.h>


void create_all_parametres(All_parametres* all_parametres)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
    //stb identification   
    set_method(data,SERIAL_NUMBER);
	all_parametres->serial_number = get_method_value_by_array(get_method(data),30);
	set_method(data,NAGRA_SERIAL_NUMBER);
	all_parametres->nagra_serial_number = get_method_value_by_array(get_method(data),30);
	set_method(data,MODEL);
	all_parametres->model = get_method_value_by_array(get_method(data),20);
	set_method(data,STB_MAC_ADDRESS);
	all_parametres->stb_mac_address = get_method_value_by_array(get_method(data),20);
	set_method(data,ETHERNET_MAC_ADDRESS);
	all_parametres->ethernet_mac_address = get_method_value_by_array(get_method(data),20);
	set_method(data,FIRMWARE_VERSION);
	all_parametres->firmware_version = get_method_value_by_array(get_method(data),40);
	set_method(data,STB_MANUFACTURING_DATE);
	all_parametres->stb_manufacturing_date = get_method_value_by_array(get_method(data),30);
	set_method(data,HARDWARE_VERSION);
	all_parametres->hardware_version = get_method_value_by_array(get_method(data),10);
	set_method(data,NETWORK_ID);
	all_parametres->network_id = get_method_value_by_array(get_method(data),50);
	set_method(data,MANUFACTURER);
	all_parametres->manufacturer = get_method_value_by_array(get_method(data),26);	



    //conditional access
    set_method(data,NAGRA_SERIAL_NUMBER);
    all_parametres->Nagra_Serial_Number = get_method_value_by_array(get_method(data),30);
    set_method(data,CA_PROVIDER_NAME);
    all_parametres->CA_Provider_Name = get_method_value_by_array(get_method(data),20);
    
    //loader data
    set_method(data,BOOT_LOADER_CRC);
    all_parametres->boot_loader_crc = get_method_value_by_array(get_method(data),30);
    set_method(data,BOOTLOADER_VERSION);
    all_parametres->boot_loader_version = get_method_value_by_array(get_method(data),5);
   
    //memoire data
    set_method(data,ADDRESSING_MEMORY);
    all_parametres->addressing_memory = get_method_value_by_array(get_method(data),30);
    set_method(data,MEMORY_BLOCK_STATUS);
    all_parametres->memory_block_status = get_method_value_by_array(get_method(data),30);
    set_method(data,USED_MEMORY);
    all_parametres->used_memory = get_method_value_by_array(get_method(data),30);
    set_method(data,TOTAL_MEMORY);
    all_parametres->total_memory = get_method_value_by_array(get_method(data),30);
    
    //network data
	set_method(data,SERIAL_NUMBER);
    all_parametres->stb_serial_number = get_method_value_by_array(get_method(data),30);
    set_method(data,STB_SUBNET_MASK);
    all_parametres->stb_subnet_mask = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    set_method(data,STB_IP_DEFAULT_GATEWAY);
    all_parametres->stb_ip_default_gateway = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
	set_method(data,STB_MAC_ADDRESS);
    all_parametres->stb_mac_address = get_method_value_by_array(get_method(data),20);   
	set_method(data,DNS_SERVER_II);
    all_parametres->dns_serverII = get_method_value_by_array(get_method(data),30);
    set_method(data,STB_ETHERNET_PORT_STATUS);//TBD without gather
    all_parametres->stb_ethernet_port_status = get_method_value_by_array(get_method(data),20);
    set_method(data,ETHERNET_MAC_ADDRESS);
    all_parametres->stb_mac_ethernet = get_method_value_by_array(get_method(data),20); 
    set_method(data,STB_IP_ADDRESS);
    all_parametres->stb_ip_address = get_method_value_by_array(get_method(data),MAX_MW_PARAM_SIZE);
    
    //software data
	set_method(data,BOOTLOADER_VERSION);
	all_parametres->boot_loader_version = get_method_value_by_array(get_method(data),5);
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	all_parametres->total_software_updates = get_method_value_by_array(get_method(data),50);
	set_method(data,DATE_TIME_LAST_STB_SOFTWARE);
	all_parametres->date_time_last_stb_software= get_method_value_by_array(get_method(data),30);
	set_method(data,TIVO_SOFTWARE_NAME);
	all_parametres->tivo_software_name= get_method_value_by_array(get_method(data),40);

    //sys_info
    set_method(data,IR_INPUT_STATUS);
    all_parametres->IR_Input_Status = get_method_value_by_array(get_method(data),30);
    set_method(data,INTERNAL_TEMPERATURE);
    all_parametres->Internal_Temperature = get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    all_parametres->CPU_Utilisation = get_method_value_by_array(get_method(data),30);
    set_method(data,HDMI_PORT_STATUS);
    all_parametres->HDMI_Port_Status = get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_RESOLUTION);
    all_parametres->Video_Resolution = get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_ASPECT_RATIO);
    all_parametres->Video_Aspect_Ratio = get_method_value_by_array(get_method(data),30);
    set_method(data,VIDEO_FORMAT);
    all_parametres->Video_Format = get_method_value_by_array(get_method(data),30);
    set_method(data,DIAGNOSTICS_PAGES_LANGUAGE);
    all_parametres->Diagnostics_Pages_Language = get_method_value_by_array(get_method(data),30);
    set_method(data,AUDIO_SETUP);
    all_parametres->Audio_Setup = get_method_value_by_array(get_method(data),30);
    set_method(data,STB_LIFE_TIME);
    all_parametres->STB_Lifetime = get_method_value_by_array(get_method(data),50);   
    set_method(data,TOTAL_STB_POWER_OFF);
    all_parametres->STB_totalPowerOff = get_method_value_by_array(get_method(data),50);   
    set_method(data,TIME_SINCE_LAST_STB_BOOT_UP);
    all_parametres->Time_since_last_STB_boot_up = get_method_value_by_array(get_method(data),50);  
    set_method(data,TOTAL_STB_REBOOT);
    all_parametres->Total_STB_Reboot = get_method_value_by_array(get_method(data),50);
    destroy_get_data();
    free(data);
}
