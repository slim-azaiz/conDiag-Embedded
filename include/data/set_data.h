#ifndef SET_DATA_H
#define SET_DATA_H


#include <string.h>
#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include <stdio.h>

/*Set data results */
#define SET_DATA_OK									0
#define SET_DATA_ERROR								(-1)

/* DBUS Connection */
#define DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS			"com.sagemcom.stb.tr69datamodel"
#define DIAGNOSTIC_MENU_DBUS_PATH_DBUS				"/com/sagemcom/stb/tr69datamodel"
#define DIAGNOSTIC_MENU_DBUS_INTERFACE_MONITORING	"com.sagemcom.stb.tr69datamodel"

/* Nvmem parameters */
#define SET_NETWORK_ID									"setNetworkId"
#define SET_IR_INPUT_ID									    "setIrInputId"

typedef struct Set_data
{
	char* method;
	char* value;
}Set_data;

 
 
void create_set_data();
void destroy_set_data();
void set_method_value(Set_data *data, char* method, char* val);
int update_method_value();
#endif //SET_DATA_H
