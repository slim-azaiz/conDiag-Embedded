#include "data/set_data.h"

void create_set_data()
{	 
	if (sc_bus_init(SC_BUS_THREADED_IOLOOP, SC_BUS_TRACE_LEVEL_WARNING, NULL) < 0)
    {
        printf( "ERROR sc_bus_init"  );
    }

    if (sc_bus_declare_name(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS) < 0)
    {
        printf(  "ERROR sc_bus_declare_name"  );
    }
}

void destroy_set_data()
{
	sc_bus_undeclare_name(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS);
	sc_bus_exit();
}
void set_method_value(Set_data *set_data, char* mtd, char* val)
{
	set_data->method = mtd;
	set_data->value = val;
}


int update_method_value(char* method,char* value)
{
	DBusMessage *msg;
	DBusMessage *reply;
	DBusMessageIter iter_base;
	DBusMessageIter args;
	int ret_error = SET_DATA_OK;
	char *ret;
	dbus_bool_t result = FALSE;
	char* val;
	
	msg = dbus_message_new_method_call(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS, DIAGNOSTIC_MENU_DBUS_PATH_DBUS,DIAGNOSTIC_MENU_DBUS_INTERFACE_MONITORING, method);

	if (msg == NULL)
	{
		printf("dbus_message_new_method_call failed on no memory");
		return SET_DATA_ERROR;
	}
	dbus_message_iter_init_append (msg, &args);
	val = malloc(sizeof(value));
	strcpy(val,value);
	dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING,&val);
	
	if (sc_bus_method_call (msg, NULL, NULL, (void *)&reply) < 0)
	{
		printf("sc_bus_method_call for %s failed",method);
		free(val);
		return SET_DATA_ERROR;
	}
	free(val);
	result = dbus_message_iter_init(reply, &iter_base);
	
	if(result == FALSE)
	{
		printf("dbus_message_iter_init for %s failed",method);
		return SET_DATA_ERROR;
	}
	dbus_message_iter_get_basic(&iter_base, &ret);
	dbus_message_unref (reply);
	/*char* data = ret;
	char* ss;
    ss = data;
	ss = ret_error;
*/	return ret_error;
}

