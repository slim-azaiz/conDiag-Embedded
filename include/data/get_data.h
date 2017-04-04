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
#define MODEL										"VELASQUEZ"
#define STB_MAC_ADDRESS								"getMACAddress_Diagnostic"
#define ETHERNET_MAC_ADDRESS						"getMACAddress_Diagnostic"
#define STB_MANUFACTURING_DATE						"TBD"
#define HARDWARE_VERSION							"getHardwareVersion"
#define NETWORK_ID									"getNetworkId"
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
#define STB_ETHERNET_PORT_STATUS 					"TBD"
#define ETHERNET_MAC_ADDRESS 						"getMACAddress_Diagnostic"
#define TV_MANUFACTURER_MODEL 						"TBD"
#define STB_IP_ADDRESS 								"getIpAddress"
#define DNS_SERVER_II								"TBD"


/* Conditional_access parameters */
 #define NAGRA_SERIAL_NUMBER						"get_STU_Number"
 #define CA_PROVIDER_NAME                           "Nagravision"
 
/*Systeme_info parameters*/
 #define IR_INPUT_STATUS							"TBD"
 #define INTERNAL_TEMPERATURE						"getThermalManagement"
 #define CPU_UTILISATION							"TBD"
 #define HDMI_PORT_STATUS							"TBD"
 #define VIDEO_RESOLUTION							"TBD"
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
#define USED_MEMORY									"TBD"
#define TOTAL_MEMORY								"TBD"

#define MAX_MW_PARAM_SIZE							128


typedef struct Get_data
{
	char* method;

}Get_data;

 
 

void create_get_data();
void destroy_get_data();
void set_method(Get_data *data,char* method);
char* get_method(Get_data *data);
char* get_method_value_by_string(char* method);
char* get_method_value_by_array(char* method,int length);
#endif //GET_DATA_H
