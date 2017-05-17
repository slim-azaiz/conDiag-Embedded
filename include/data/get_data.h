#ifndef GET_DATA_H
#define GET_DATA_H

#include <string.h>
#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include <stdio.h>

/*Get data results */
#define GET_DATA_OK									0
#define GET_DATA_ERROR								(-1)
/* DBUS Connection */
#define DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS			"com.sagemcom.stb.tr69datamodel"
#define DIAGNOSTIC_MENU_DBUS_PATH_DBUS				"/com/sagemcom/stb/tr69datamodel"
#define DIAGNOSTIC_MENU_DBUS_INTERFACE_MONITORING	"com.sagemcom.stb.tr69datamodel"
/* STB Identification parameters */
#define SERIAL_NUMBER								"getSerialNumber"
#define NAGRA_SERIAL_NUMBER							"get_STU_Number"
#define MODEL										"get_model"
#define STB_MAC_ADDRESS								"getMACAddress_Diagnostic"
#define ETHERNET_MAC_ADDRESS						"getMACAddress_Diagnostic"
#define STB_MANUFACTURING_DATE						"TBD"
#define HARDWARE_VERSION							"getHardwareVersion"
#define NETWORK_ID									"getTcdMode"/*"getNetworkId"*/
#define MANUFACTURER								"getManufacturer"

/* Nvmem parameters */
#define TCD_MODE									"getTcdMode"
#define SI_MILTICAST_ADDRESS						"getSiMulticastAddress"
#define VM_INSTALLER_FREQUENCY						"getVmInstallerFrequency"
#define VM_INSTALLER_SYMBOLRATE						"getVmInstallerSymbolRate"
#define VM_INSTALLER_MODULATION						"getVmInstallerModulation"

/* Software parameters */
#define BOOTLOADER_VERSION							"getLoaderVersion"
#define TOTAL_SOFTWARE_UPDATES						"getDownload_counter"
#define DATE_TIME_LAST_STB_SOFTWARE					"get_Last_Download_Date"
#define TIVO_SOFTWARE_NAME							"get_SW_version"
/* Installation & Network addressing */

#define STB_SUBNET_MASK 							"getSubnetMask"
#define STB_IP_DEFAULT_GATEWAY 						"getDefaultGateway"
#define STB_MAC_ADDRESS 							"getMACAddress_Diagnostic"
#define FIRMWARE_VERSION 							"get_SW_version"
#define STB_ETHERNET_PORT_STATUS 					"GetEthernetportstate"
#define ETHERNET_MAC_ADDRESS 						"getMACAddress_Diagnostic"
#define TV_MANUFACTURER_MODEL 						"TBD"
#define STB_IP_ADDRESS 								"getIpAddress"
#define DNS_SERVER_II								"TBD"


/* Conditional_access parameters */
 #define NAGRA_SERIAL_NUMBER						"get_STU_Number"
 #define CA_PROVIDER_NAME                           "get_ca_provider_name"
 
/*Systeme_info parameters*/
 #define IR_INPUT_STATUS							"TBD"//"get_ir_input_status"
 #define INTERNAL_TEMPERATURE						"getThermalManagement"
 #define CPU_UTILISATION							"get_cpu_utilization"
 #define HDMI_PORT_STATUS							"getHdmiConnectionStatus"
 #define VIDEO_RESOLUTION							"GetCurrentResolution"
 #define VIDEO_ASPECT_RATIO							"TBD"
 #define VIDEO_FORMAT								"TBD"
 #define DIAGNOSTICS_PAGES_LANGUAGE					"TBD"
 #define AUDIO_SETUP								"TBD"
 #define STB_LIFE_TIME								"getLifeTime"
 #define TIME_SINCE_LAST_STB_BOOT_UP				"getStandbyTime"
 #define TOTAL_STB_POWER_OFF						"getStandbyCounter"
 #define RESET_TIME_SINCE_LAST_BOOT_UP				"resetTimeSinceLastBootUp"
 #define RESET_TOTAL_POWER_OFF						"resetTotalPowerOff"
 #define RESET_TOTAL_SOFTWARE_UPDATE				"resetTotalSoftwareUpdate"
 #define RESET_TOTAL_REBOOT							"resetTotalReboot"
 #define TOTAL_STB_REBOOT							"getbootcounter"
 /*Loader parameters*/
 #define BOOT_LOADER_CRC 							"TBD"
 /*Memory Map*/
#define ADDRESSING_MEMORY							"TBD"
#define MEMORY_BLOCK_STATUS							"TBD"
#define USED_MEMORY									"get_used_memory"
#define TOTAL_MEMORY								"get_total_memory"
/* Nvmem parameters */
#define TCD_MODE									"getTcdMode"
#define SI_MILTICAST_ADDRESS						"getSiMulticastAddress"
#define VM_INSTALLER_FREQUENCY						"getVmInstallerFrequency"
#define VM_INSTALLER_SYMBOLRATE						"getVmInstallerSymbolRate"
#define VM_INSTALLER_MODULATION						"getVmInstallerModulation"
 
/*Tuner parametres */
#define VirtualTunerMcastAddr                       "getVirtualTunerMcastAddr"
#define VirtualTunerMcastPortNum					"getVirtualTunerMcastPortNum"
#define VirtualTunerSocketStatus					"getVirtualTunerSocketStatus"
#define VirtualTunerPMTStatus				       	"getVirtualTunerPMTStatus"
#define VirtualTunerLastPAT					    	"getVirtualTunerLastPAT"
#define VirtualTunerLastCAT					    	"getVirtualTunerLastCAT"

#define TunerMcastStreamType                        "getTunerMcastStreamType"
#define TunerStat                    				"getTunerStat"
#define TunerCurrentFrequency						"getTunerCurrentFrequency"
#define TunerPMTStatus						       	"getTunerPMTStatus"
#define TunerLastPAT						    	"getTunerLastPAT"
#define TunerLastCAT						    	"getTunerLastCAT"

#define TSIndex                                     "getTSIndex"         
#define TSFrequency                                 "getTSFrequency" 
#define TSLockStatus                                "getTSLockStatus" 
#define TSInputLevelDB                              "getTSInputLevelDB" 
#define TSErrorRatePreRS                            "getTSErrorRatePreRS" 
#define TSErrorRatePostRS                           "getTSErrorRatePostRS" 
#define ErrorRatePreRSHistorical                    "getErrorRatePreRSHistorical" 
#define ErrorRatePostRSHistorical                   "getErrorRatePostRSHistorical"
#define TSSNREstimate                               "getTSSNREstimate"
#define TSLastTunedTimestamp                        "getTSLastTunedTimestamp" 
#define TSTunerID                                   "getTSTunerID"
#define TSTransportStreamID                         "getTSTransportStreamID" 

#define MAX_MW_PARAM_SIZE							128


typedef struct Get_data
{
	char* method;

}Get_data;

 
 

void create_get_data();
char* hexdec(const char *hex );
void destroy_get_data();
void set_method(Get_data *data,char* method);
char* get_method(Get_data *data);
char* get_method_value_by_string(char* method);
char* get_method_value_by_array(char* method,int length);
#endif //GET_DATA_H
