#include "data/all_parametres.h"


//identification
int json_stb_identification(char** result){
    char* stb_identification_parameter[SIZE_IDENTIFICATION] = {"SERIAL NUMBER","NAGRA SERIAL_NUMBER","MODEL","STB MAC ADDRESS","ETHERNET MAC ADDRESS","FIRMWARE VERSION","STB MANUFACTURING_DATE","HARDWARE VERSION","NETWORK_ID","MANUFACTURER"};
    char* stb_identification_value[SIZE_IDENTIFICATION] = {SERIAL_NUMBER,NAGRA_SERIAL_NUMBER,MODEL,STB_MAC_ADDRESS,ETHERNET_MAC_ADDRESS,FIRMWARE_VERSION,STB_MANUFACTURING_DATE,HARDWARE_VERSION,NETWORK_ID,MANUFACTURER};
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_IDENTIFICATION ; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((stb_identification_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(stb_identification_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
//conditional_access    
int json_conditional_access(char** result){
    char* conditional_access_parameter[SIZE_CONDITIONAL_ACCESS] = {"Nagra Serial Number","CA Provider Name"};
    char* conditional_access_value[SIZE_CONDITIONAL_ACCESS] = {NAGRA_SERIAL_NUMBER,CA_PROVIDER_NAME};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_CONDITIONAL_ACCESS; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((conditional_access_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(conditional_access_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    
    //loader data
int json_loader(char** result){
    char* loader_parameter[SIZE_LOADER] = {"Boot loader crc","Boot loader version"};
    char* loader_value[SIZE_LOADER] = {BOOT_LOADER_CRC,BOOTLOADER_VERSION};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_LOADER; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((loader_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(loader_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    
    //memoire data
int json_memory(char** result){
    char* memory_parameter[SIZE_MEMORY] = {"Addressing memory","Memory block status","Used_Memory","Total memory"};
    char* memory_value[SIZE_MEMORY] = {ADDRESSING_MEMORY,MEMORY_BLOCK_STATUS,USED_MEMORY,TOTAL_MEMORY};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_MEMORY; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((memory_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(memory_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //memoire real_time
int json_memory_real_time(char** result){
    char* memory_parameter[SIZE_MEMORY_REAL_TIME] = {"Used_Memory"};
    char* memory_value[SIZE_MEMORY_REAL_TIME] = {USED_MEMORY};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_MEMORY_REAL_TIME; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((memory_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(memory_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //network data
int json_network(char** result){
    char* network_parameter[SIZE_NETWORK] = {"STB serial number","STB subnet mask","STB ip default_gateway","STB mac address","STB_ethernet_Port_Status","STB mac ethernet","STB ip address","dns serverII"};
    char* network_value[SIZE_NETWORK] = {SERIAL_NUMBER,STB_SUBNET_MASK,STB_IP_DEFAULT_GATEWAY,STB_MAC_ADDRESS,STB_ETHERNET_PORT_STATUS, ETHERNET_MAC_ADDRESS, STB_IP_ADDRESS,DNS_SERVER_II};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_NETWORK;i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((network_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(network_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //network_realtime
int json_network_real_time(char** result){
    char* network_parameter[SIZE_NETWORK_REAL_TIME] = {"STB_ethernet_Port_Status"};
    char* network_value[SIZE_NETWORK_REAL_TIME] = {STB_ETHERNET_PORT_STATUS};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_NETWORK_REAL_TIME;i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((network_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(network_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //software data
int json_software(char** result){
    char* software_parameter[SIZE_SOFTWARE] = {"Boot loader version","TotalSoftwareUpdates","Date time last stb software","TiVo software name"};
    char* software_value[SIZE_SOFTWARE] = {BOOTLOADER_VERSION,TOTAL_SOFTWARE_UPDATES,DATE_TIME_LAST_STB_SOFTWARE,TIVO_SOFTWARE_NAME};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_SOFTWARE; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((software_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(software_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //software real time
int json_software_real_time(char** result){
    char* software_parameter[SIZE_SOFTWARE_REAL_TIME] = {"TotalSoftwareUpdates"};
    char* software_value[SIZE_SOFTWARE_REAL_TIME] = {TOTAL_SOFTWARE_UPDATES};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_SOFTWARE_REAL_TIME; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((software_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(software_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //sys_info
int json_sys_info(char** result){
    char* sys_info_parameter[SIZE_SYSINFO] = {"IR Input Status","Internal_Temperature","CPU_Utilisation","HDMI_port_Status","STB Lifetime","STB total Power Off","Time since last STB boot up","Total STB Reboot","Video Resolution","Video Aspect_Ratio","Video Format","Diagnostics Pages Language","Audio Setup"};
    char* sys_info_value[SIZE_SYSINFO] = { IR_INPUT_STATUS,INTERNAL_TEMPERATURE,CPU_UTILISATION,HDMI_PORT_STATUS,VIDEO_RESOLUTION,STB_LIFE_TIME,TOTAL_STB_POWER_OFF,TIME_SINCE_LAST_STB_BOOT_UP,TOTAL_STB_REBOOT,VIDEO_ASPECT_RATIO,VIDEO_FORMAT,DIAGNOSTICS_PAGES_LANGUAGE,AUDIO_SETUP};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_SYSINFO; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], VALUE,get_method_value_by_array((sys_info_value)[i],30));
        cJSON_AddStringToObject(objects[i], PARAMETER,(sys_info_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //sys_info_real_time
int json_sys_info_real_time(char** result){
    char* sys_info_parameter[SIZE_SYSINFO] = {"Internal_Temperature","CPU_Utilisation","HDMI_port_Status"};
    char* sys_info_value[SIZE_SYSINFO] = { INTERNAL_TEMPERATURE,CPU_UTILISATION,HDMI_PORT_STATUS};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_SYSINFO_REAL_TIME; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((sys_info_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(sys_info_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //nvmem
int json_nvmem(char** result){
    char* nvmem_parameter[SIZE_NVMEM] = {"TCD_MODE","SI_MILTICAST_ADDRESS","VM_INSTALLER_FREQUENCY","VM_INSTALLER_SYMBOLRATE","VM_INSTALLER_MODULATION"};
    char* nvmem_value[SIZE_NVMEM] = {TCD_MODE,SI_MILTICAST_ADDRESS,VM_INSTALLER_FREQUENCY,VM_INSTALLER_SYMBOLRATE,VM_INSTALLER_MODULATION};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_NVMEM; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "parameter",(nvmem_parameter)[i]);    

        if(!strcmp((nvmem_parameter)[i],"TCD_MODE")){
                if(strcmp(hexdec(get_method_value_by_array(TCD_MODE,30)),"1")==0){
                    cJSON_AddStringToObject(objects[i], "value","QAM");
                }
                else if(strcmp(hexdec(get_method_value_by_array(TCD_MODE,30)),"2")==0){
                    cJSON_AddStringToObject(objects[i], "value","IP");
                }
                else{
                    cJSON_AddStringToObject(objects[i], "value","UNINIITALIZED");
                }
         }
         else if(!strcmp((nvmem_parameter)[i],VM_INSTALLER_MODULATION)){
             if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"16")==0){
                    cJSON_AddStringToObject(objects[i], "value","16");
             }
             else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"32")==0){
                    cJSON_AddStringToObject(objects[i], "value","32");
             }                                              
             else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"64")==0){
                    cJSON_AddStringToObject(objects[i], "value","64");
             }                                           
             else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"128")==0){
                    cJSON_AddStringToObject(objects[i], "value","128");
             }                                              
             else {
                    cJSON_AddStringToObject(objects[i], "value","256");
             }
        }else
            cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((nvmem_value)[i],30));
        }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //virtual_tuner
int json_virtual_tuner(char** result){
    char* virtual_tuner_parameter[SIZE_VIRTUAL_TUNER] = {"VirtualTunerMcastAddr","VirtualTunerMcastPortNum","VirtualTunerSocketStatus","VirtualTunerPMTStatus","VirtualTunerLastPAT","VirtualTunerLastCAT"};
    char* virtual_tuner_value[SIZE_VIRTUAL_TUNER] = {VirtualTunerMcastAddr,VirtualTunerMcastPortNum,VirtualTunerSocketStatus,VirtualTunerPMTStatus,VirtualTunerLastPAT,VirtualTunerLastCAT};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_VIRTUAL_TUNER; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((virtual_tuner_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(virtual_tuner_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
    //tuner
int json_tuner(char** result){
    char* tuner_parameter[SIZE_TUNER] = {"TunerMcastStreamType","TunerStat","TunerCurrentFrequency","TunerPMTStatus","TunerLastPAT","TunerLastCAT","TSIndex","TSFrequency","TSLockStatus","TSInputLevelDB","TSErrorRatePreRS","TSErrorRatePostRS","ErrorRatePreRSHistorical","ErrorRatePostRSHistorical","TSSNREstimate","TSLastTunedTimestamp","TSTunerID","TSTransportStreamID"};

    char* tuner_value[SIZE_TUNER] = {TunerMcastStreamType,TunerStat,TunerCurrentFrequency,TunerPMTStatus,TunerLastPAT,TunerLastCAT,TSIndex,TSFrequency,TSLockStatus,TSInputLevelDB,TSErrorRatePreRS,TSErrorRatePostRS,ErrorRatePreRSHistorical,ErrorRatePostRSHistorical, TSSNREstimate, TSLastTunedTimestamp,TSTunerID,TSTransportStreamID};
    
    cJSON *objects[1];
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < SIZE_TUNER; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",get_method_value_by_array((tuner_value)[i],30));
        cJSON_AddStringToObject(objects[i], "parameter",(tuner_parameter)[i]);    
    }
    *result = strdup(cJSON_Print(root)) ;
    return RESULT_SUCCESS;
}
