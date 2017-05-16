#include "../../include/data/all_parametres.h"
#include <stdio.h>


void create_all_parametres(All_parametres* all_parametres)
{
    int i =59;
   // members = (char *)malloc(40 * 2 * sizeof(char*));
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
    //stb identification   
	all_parametres->members[0][1]= "serial number" ;
	all_parametres->members[1][1]= "Nagra serial number" ;
	all_parametres->members[2][1]= "Model" ;
	all_parametres->members[3][1]="STB mac address" ;
	all_parametres->members[4][1]="Ethernet mac address" ;
	all_parametres->members[5][1]="Firmware version" ;
	all_parametres->members[6][1]="STB manufacturing date" ;
	all_parametres->members[7][1]="Hardware version";
	all_parametres->members[8][1]="NETWORK_ID" ;
	all_parametres->members[9][1]="Manufacturer" ;	
    //conditional access
    all_parametres->members[10][1]="Nagra Serial Number" ;
    all_parametres->members[11][1]="CA Provider Name" ;
    //loader data
    all_parametres->members[12][1]="Boot loader crc" ;
    all_parametres->members[13][1]="Boot loader version" ;
    //memoire data
    all_parametres->members[14][1]="Addressing memory" ;
    all_parametres->members[15][1]="Memory block status" ;
    all_parametres->members[16][1]="Used_Memory" ;
    all_parametres->members[17][1]="Total memory" ;
    //network data
    all_parametres->members[18][1]="STB serial number" ;
    all_parametres->members[19][1]="STB subnet mask" ;
    all_parametres->members[20][1]="STB ip default_gateway" ;
    all_parametres->members[21][1]="STB mac address" ;   
    all_parametres->members[22][1]="dns serverII" ;
    all_parametres->members[23][1]="STB_ethernet_Port_Status" ;
    all_parametres->members[24][1]="STB mac ethernet" ; 
    all_parametres->members[25][1]="STB ip address" ;
    //software data
	all_parametres->members[26][1]="Boot loader version" ;
	all_parametres->members[27][1]="TotalSoftwareUpdates" ;
	all_parametres->members[28][1]="Date time last stb software";
	all_parametres->members[29][1]="TiVo software name";
    //sys_info
    all_parametres->members[30][1]="IR Input Status" ;
    all_parametres->members[31][1]="Internal_Temperature" ;
    all_parametres->members[32][1]="CPU_Utilisation" ;
    all_parametres->members[33][1]="HDMI_port_Status" ;
    all_parametres->members[34][1]="Video Resolution" ;
    all_parametres->members[35][1]="Video Aspect_Ratio" ;
    all_parametres->members[36][1]="Video Format" ;
    all_parametres->members[37][1]="Diagnostics Pages Language" ;
    all_parametres->members[38][1]="Audio Setup" ;
    all_parametres->members[39][1]="STB Lifetime" ;   
    all_parametres->members[40][1]="STB total Power Off" ;   
    all_parametres->members[41][1]="Time since last STB boot up" ;  
    all_parametres->members[42][1]= "Total STB Reboot" ;
    //nvmem
    all_parametres->members[43][1]="TCD_MODE" ;
    all_parametres->members[44][1]="SI_MILTICAST_ADDRESS" ;
    all_parametres->members[45][1]="VM_INSTALLER_FREQUENCY" ;
    all_parametres->members[46][1]="VM_INSTALLER_SYMBOLRATE" ;
    //all_parametres->members[46][0]= get_method_value_by_array(get_method(data),30);
    all_parametres->members[47][1]="VM_INSTALLER_MODULATION" ;
    //virtual_tuner
	all_parametres->members[48][1]="VirtualTunerMcastAddr";
	all_parametres->members[49][1]="VirtualTunerMcastPortNum";
    all_parametres->members[50][1]="VirtualTunerSocketStatus" ;
    all_parametres->members[51][1]="VirtualTunerPMTStatus" ;
    all_parametres->members[52][1]="VirtualTunerLastPAT" ;
    all_parametres->members[53][1]="VirtualTunerLastCAT" ;
    //tuner
    all_parametres->members[54][1]="TunerMcastStreamType" ;
    all_parametres->members[55][1]="TunerStat" ;
    all_parametres->members[56][1]="TunerCurrentFrequency" ;
    all_parametres->members[57][1]="TunerPMTStatus" ;
    all_parametres->members[58][1]="TunerLastPAT" ;
    all_parametres->members[59][1]="TunerLastCAT" ;   
    i++;
    all_parametres->members[i][1]="TSIndex";i++;   
    all_parametres->members[i][1]="TSFrequency";i++;   
    all_parametres->members[i][1]="TSLockStatus";i++;   
    all_parametres->members[i][1]="TSInputLevelDB";i++;   
    all_parametres->members[i][1]="TSErrorRatePreRS";i++;   
    all_parametres->members[i][1]="TSErrorRatePostRS";i++;   
    all_parametres->members[i][1]="ErrorRatePreRSHistorical";i++;   
    all_parametres->members[i][1]="ErrorRatePostRSHistorical";i++;   
    all_parametres->members[i][1]="TSSNREstimate";i++;   
    all_parametres->members[i][1]="TSLastTunedTimestamp";i++;   
    all_parametres->members[i][1]="TSTunerID";i++;   
    all_parametres->members[i][1]="TSTransportStreamID";i++;   

    destroy_get_data();
    free(data);
}

void get_stb_identification_parametres(All_parametres* all_parametres){
	all_parametres->members[0][0]= get_method_value_by_array(SERIAL_NUMBER,30);
	all_parametres->members[1][0]= get_method_value_by_array(NAGRA_SERIAL_NUMBER,30);
	all_parametres->members[2][0]= get_method_value_by_array(MODEL,20);
	all_parametres->members[3][0]= get_method_value_by_array(STB_MAC_ADDRESS,20);
	all_parametres->members[4][0]= get_method_value_by_array(ETHERNET_MAC_ADDRESS,20);
	all_parametres->members[5][0]= get_method_value_by_array(FIRMWARE_VERSION,40);
	all_parametres->members[6][0]= get_method_value_by_array(STB_MANUFACTURING_DATE,30);
	all_parametres->members[7][0]= get_method_value_by_array(HARDWARE_VERSION,10);
	all_parametres->members[8][0]= get_method_value_by_array(NETWORK_ID,50);
	all_parametres->members[9][0]= get_method_value_by_array(MANUFACTURER,26);	
}
void get_memory_parametres(All_parametres* all_parametres){
    //memoire data
    all_parametres->members[14][0]= get_method_value_by_array(ADDRESSING_MEMORY,30);
    all_parametres->members[15][0]= get_method_value_by_array(MEMORY_BLOCK_STATUS,30);
    all_parametres->members[16][0]= get_method_value_by_array(USED_MEMORY,30);
    all_parametres->members[17][0]= get_method_value_by_array(TOTAL_MEMORY,30);
}
void get_tuner_parametres(All_parametres* all_parametres){
    all_parametres->members[54][0]= get_method_value_by_array(TunerMcastStreamType,30);
    all_parametres->members[55][0]= get_method_value_by_array(TunerStat,30);
    all_parametres->members[56][0]= get_method_value_by_array(TunerCurrentFrequency,30);
    all_parametres->members[57][0]= get_method_value_by_array(TunerPMTStatus,30);
    all_parametres->members[58][0]= get_method_value_by_array(TunerLastPAT,30);
    all_parametres->members[59][0]= get_method_value_by_array(TunerLastCAT,50);
    int i = 60;
    all_parametres->members[i][0]= get_method_value_by_array(TSIndex,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSFrequency,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSLockStatus,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSInputLevelDB,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSErrorRatePreRS,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSErrorRatePostRS,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(ErrorRatePreRSHistorical,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(ErrorRatePostRSHistorical,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSSNREstimate,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSLastTunedTimestamp,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSTunerID,50);i++;
    all_parametres->members[i][0]= get_method_value_by_array(TSTransportStreamID,50);   
}

void get_virtual_tuner_parametres(All_parametres* all_parametres){
	//virtual tuner
    all_parametres->members[48][0]= get_method_value_by_array(VirtualTunerMcastAddr,30);
	all_parametres->members[49][0]= get_method_value_by_array(VirtualTunerMcastPortNum,40);
    all_parametres->members[50][0]= get_method_value_by_array(VirtualTunerSocketStatus,30);
    all_parametres->members[51][0]= get_method_value_by_array(VirtualTunerPMTStatus,11);
    all_parametres->members[52][0]= get_method_value_by_array(VirtualTunerLastPAT,30);
    all_parametres->members[53][0]= get_method_value_by_array(VirtualTunerLastCAT,30);
}
void get_nvmem_parametres(All_parametres* all_parametres){
    //nvmem
    if(strcmp(hexdec(get_method_value_by_array(TCD_MODE,30)),"1")==0){
        printf("TCD_MODE QAM");
        all_parametres->members[43][0]="QAM"; 
    }
    else if(strcmp(hexdec(get_method_value_by_array(TCD_MODE,30)),"2")==0){
        printf("TCD_MODE IP");
        all_parametres->members[43][0]="IP"; 
    }
    else{
        printf("TCD_MODE UNINIITALIZED");
        all_parametres->members[43][0]="UNINIITALIZED"; 
    }
    //printf("TCD_MODE =%s",all_parametres->members[43][0]);
    all_parametres->members[44][0]= get_method_value_by_array(SI_MILTICAST_ADDRESS,30);
    all_parametres->members[45][0]= get_method_value_by_array(VM_INSTALLER_FREQUENCY,30);
    //all_parametres->members[46][0]= hexdec(get_method_value_by_array(VM_INSTALLER_SYMBOLRATE,30));
    all_parametres->members[46][0]= get_method_value_by_array(VM_INSTALLER_SYMBOLRATE,30);
    if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"16")==0){
        all_parametres->members[47][0]="16"; 
    }
    else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"32")==0){
        all_parametres->members[47][0]="32";        
    }                                              
    else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"64")==0){
        all_parametres->members[47][0]="64";        
        }                                           
    else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"128")==0){
        all_parametres->members[47][0]="128";      
    }                                               
    else if(strcmp(hexdec(get_method_value_by_array(VM_INSTALLER_MODULATION,30)),"256")==0){
        all_parametres->members[47][0]="256"; 
    }
    else{
        all_parametres->members[47][0]="64"; 
    }
}
void get_software_parametres(All_parametres* all_parametres){
    //software data
	all_parametres->members[26][0]= get_method_value_by_array(BOOTLOADER_VERSION,5);
	all_parametres->members[27][0]= get_method_value_by_array(TOTAL_SOFTWARE_UPDATES,50);
	all_parametres->members[28][0]= get_method_value_by_array(DATE_TIME_LAST_STB_SOFTWARE,30);
	all_parametres->members[29][0]= get_method_value_by_array(TIVO_SOFTWARE_NAME,40);
}
void get_network_parametres(All_parametres* all_parametres){
    //network data
    all_parametres->members[18][0]= get_method_value_by_array(SERIAL_NUMBER,30);
    all_parametres->members[19][0]= get_method_value_by_array(STB_SUBNET_MASK,MAX_MW_PARAM_SIZE);
    all_parametres->members[20][0]= get_method_value_by_array(STB_IP_DEFAULT_GATEWAY,MAX_MW_PARAM_SIZE);
    all_parametres->members[21][0]= get_method_value_by_array(STB_MAC_ADDRESS,20);   
    all_parametres->members[22][0]= get_method_value_by_array(DNS_SERVER_II,30);
    all_parametres->members[23][0]= get_method_value_by_array(STB_ETHERNET_PORT_STATUS,20);
    all_parametres->members[24][0]= get_method_value_by_array(ETHERNET_MAC_ADDRESS,20); 
    all_parametres->members[25][0]= get_method_value_by_array(STB_IP_ADDRESS,MAX_MW_PARAM_SIZE);
}
void get_loader_parametres(All_parametres* all_parametres){
    //loader data
    all_parametres->members[12][0]= get_method_value_by_array(BOOT_LOADER_CRC,30);
    all_parametres->members[13][0]= get_method_value_by_array(BOOTLOADER_VERSION,5);
}
void get_conditional_access_parametres(All_parametres* all_parametres){
    //conditional access
    all_parametres->members[10][0]= get_method_value_by_array(NAGRA_SERIAL_NUMBER,30);
    all_parametres->members[11][0]= get_method_value_by_array(CA_PROVIDER_NAME,20);
}

void get_sys_info_parametres(All_parametres* all_parametres){
    //sysInfo
    all_parametres->members[30][0]= get_method_value_by_array(IR_INPUT_STATUS,30);
    all_parametres->members[31][0]= get_method_value_by_array(INTERNAL_TEMPERATURE,11);
    all_parametres->members[32][0]= get_method_value_by_array(CPU_UTILISATION,30);
    all_parametres->members[33][0]= get_method_value_by_array(HDMI_PORT_STATUS,30);
    all_parametres->members[34][0]= get_method_value_by_array(VIDEO_RESOLUTION,30);
    all_parametres->members[35][0]= get_method_value_by_array(VIDEO_ASPECT_RATIO,30);
    all_parametres->members[36][0]= get_method_value_by_array(VIDEO_FORMAT,30);
    all_parametres->members[37][0]= get_method_value_by_array(DIAGNOSTICS_PAGES_LANGUAGE,30);
    all_parametres->members[38][0]= get_method_value_by_array(AUDIO_SETUP,30);
    all_parametres->members[39][0]= get_method_value_by_array(STB_LIFE_TIME,50);   
    all_parametres->members[40][0]= get_method_value_by_array(TOTAL_STB_POWER_OFF,50);   
    all_parametres->members[41][0]= get_method_value_by_array(TIME_SINCE_LAST_STB_BOOT_UP,50);  
    all_parametres->members[42][0]= get_method_value_by_array(TOTAL_STB_REBOOT,50);
}

