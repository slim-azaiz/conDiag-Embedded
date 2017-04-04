#ifndef SYS_INFO_DATA_H
#define SYS_INFO_DATA_H
#include "get_data.h"


typedef struct Sys_info_data 
{
    char* IR_Input_Status;
    char* Internal_Temperature;
    char* CPU_Utilisation;
    char* HDMI_Port_Status;
    char* Video_Resolution;
    char* Video_Aspect_Ratio;
    char* Video_Format;
    char* Ethernet_Port_Status;
    char* Diagnostics_Pages_Language;
    char* Audio_Setup;
    char* STB_Lifetime;
    char* STB_totalPowerOff;
    char* Time_since_last_STB_boot_up;
	char* Total_STB_Reboot;
}Sys_info_data;

void create_Sys_info_data(Sys_info_data *Sys_info_data);
 void destroy_Sys_info_data();
#endif // SYS_INFO_DATA_H
