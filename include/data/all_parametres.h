#include <stdio.h>

#include "get_data.h"
#include "cjson/cJSON.h"

#define TCD_MODE_UNINITIALIZED	"0"
#define TCD_MODE_QAM			"1"
#define TCD_MODE_IP				"2"
#define MODULATION_QAM_16		"16"
#define MODULATION_QAM_32		"32"
#define MODULATION_QAM_64		"64"
#define MODULATION_QAM_128		"128"
#define MODULATION_QAM_256		"256"

#define SIZE_IDENTIFICATION       10
#define SIZE_LOADER               2
#define SIZE_NETWORK              8
#define SIZE_NETWORK_REAL_TIME              1
#define SIZE_SOFTWARE             4
#define SIZE_SOFTWARE_REAL_TIME             1
#define SIZE_TUNER                18
#define SIZE_VIRTUAL_TUNER        6
#define SIZE_CONDITIONAL_ACCESS   2
#define SIZE_NVMEM                5
#define SIZE_SYSINFO              13
#define SIZE_SYSINFO_REAL_TIME              3
#define SIZE_MEMORY               4
#define SIZE_MEMORY_REAL_TIME               1



int json_stb_identification(char**);
int json_software(char**);
int json_software_real_time(char**);
int json_loader(char**);
int json_sys_info(char**);
int json_sys_info_real_time(char**);
int json_memory(char**);
int json_memory_real_time(char**);
int json_network(char**);
int json_network_real_time(char**);
int json_nvmem(char**);
int json_tuner(char**);
int json_virtual_tuner(char**);
int json_conditional_access(char**);
