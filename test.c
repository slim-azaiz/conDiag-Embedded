#include <stdio.h>

typedef struct  
{
    //stb_identification
    char* serial_number           ;
	char* nagra_serial_number     ;
	char* model                   ;
	char* ethernet_mac_address    ;
	char* firmware_version        ;
	char* stb_manufacturing_date  ;
	char* hardware_version        ;
}All_parametres;
typedef struct 
{
        char* v[6];
} All_parametres;
int main(){
    All_parametres all_parametres; 
    char *value = &(all_parametres.serial_number);
    int i;
    for (i = 0; i < sizeof(all_parametres); i++)
        printf("%s\nsecond param = \n",all_parametres[i]);
    return 0;
}

