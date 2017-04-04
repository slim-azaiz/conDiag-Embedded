#include "../../include/data/sys_info_data.h"


void destroy_sys_info_data()
{
	
}

void create_sys_info_data(Sys_info_data * sys_info_data)
{
    Get_data *data = malloc(sizeof(Get_data));
   

    create_get_data();



    set_method(data,IR_INPUT_STATUS);
    sys_info_data->IR_Input_Status = get_method_value_by_string(get_method(data));
    set_method(data,INTERNAL_TEMPERATURE);
    sys_info_data->Internal_Temperature = get_method_value_by_array(get_method(data),11);
    set_method(data,CPU_UTILISATION);
    sys_info_data->CPU_Utilisation = get_method_value_by_string(get_method(data));
    set_method(data,HDMI_PORT_STATUS);
    sys_info_data->HDMI_Port_Status = get_method_value_by_string(get_method(data));
    set_method(data,VIDEO_RESOLUTION);
    sys_info_data->Video_Resolution = get_method_value_by_string(get_method(data));
    set_method(data,VIDEO_ASPECT_RATIO);
    sys_info_data->Video_Aspect_Ratio = get_method_value_by_string(get_method(data));
    set_method(data,VIDEO_FORMAT);
    sys_info_data->Video_Format = get_method_value_by_string(get_method(data));
    set_method(data,STB_ETHERNET_PORT_STATUS);
    sys_info_data->Ethernet_Port_Status = get_method_value_by_string(get_method(data));
    set_method(data,DIAGNOSTICS_PAGES_LANGUAGE);
    sys_info_data->Diagnostics_Pages_Language = get_method_value_by_string(get_method(data));
    set_method(data,AUDIO_SETUP);
    sys_info_data->Audio_Setup = get_method_value_by_string(get_method(data));
    set_method(data,STB_LIFE_TIME);
    sys_info_data->STB_Lifetime = get_method_value_by_array(get_method(data),50);   
    set_method(data,TOTAL_STB_POWER_OFF);
    sys_info_data->STB_totalPowerOff = get_method_value_by_array(get_method(data),50);   
    set_method(data,TIME_SINCE_LAST_STB_BOOT_UP);
    sys_info_data->Time_since_last_STB_boot_up = get_method_value_by_array(get_method(data),50);  
    set_method(data,TOTAL_STB_REBOOT);
    sys_info_data->Total_STB_Reboot = get_method_value_by_array(get_method(data),50);


    destroy_get_data();
    free(data);
}
