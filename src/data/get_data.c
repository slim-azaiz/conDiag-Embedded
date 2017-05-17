#include "data/get_data.h"

void create_get_data()
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

void destroy_get_data()
{
	sc_bus_undeclare_name(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS);
	sc_bus_exit();
}

void set_method(Get_data *get_data,char* mtd)
{
	get_data->method = mtd;
}

char* get_method(Get_data *get_data)
{
	return get_data->method;
}
char* get_method_value_by_string(char* method)
{
	DBusMessage *msg;
	DBusMessage *reply;
	DBusMessageIter iter_base;
	char *param;
	dbus_bool_t result = FALSE;
	
	msg = dbus_message_new_method_call(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS, DIAGNOSTIC_MENU_DBUS_PATH_DBUS,DIAGNOSTIC_MENU_DBUS_INTERFACE_MONITORING, method);

	if (msg == NULL)
	{
		printf(  "dbus_message_new_method_call failed on no memory"  );
		return "";
	}
	
	if (sc_bus_method_call (msg, NULL, NULL, (void *)&reply) < 0)
	{
		printf(  "sc_bus_method_call for%s    failed",method  );
		return "";
	}
	result = dbus_message_iter_init(reply, &iter_base);
	
	if(result == FALSE)
	{
		printf(  "dbus_message_iter_init for %s failed",method);
        return "";
	}
	dbus_message_iter_get_basic(&iter_base, &param);
	dbus_message_unref (reply);
	return param;
}

char* get_method_value_by_array(char* method,int length)
{
	DBusMessage *msg;
	DBusMessage *reply;
	DBusMessageIter iter_base,sub;
	char *param;
	
	msg = dbus_message_new_method_call(DIAGNOSTIC_MENU_DBUS_SERVICE_DBUS, DIAGNOSTIC_MENU_DBUS_PATH_DBUS,DIAGNOSTIC_MENU_DBUS_INTERFACE_MONITORING, method);

	if (msg == NULL)
	{
		printf(  "dbus_message_new_method_call failed on no memory"  );
		return "";
	}
	
	if (sc_bus_method_call (msg, NULL, NULL, (void *)&reply) < 0)
	{
		printf("sc_bus_method_call for "  " failed"  );
		return "";
	}
	dbus_message_iter_init(reply, &iter_base);

	if (dbus_message_iter_get_arg_type(&iter_base)==DBUS_TYPE_ARRAY)
	{
		dbus_message_iter_recurse (&iter_base, &sub);

		if (dbus_message_iter_get_arg_type(&sub)==DBUS_TYPE_BYTE)
		{
				dbus_message_iter_get_fixed_array (&sub, &param, &length);
                //printf("%ss",string data(param));
                char* result= param;
				return result;
		}
	}
	return "";
}
 int hex_to_int(char c){ 
         int first = c / 16 - 3; 
         int second = c % 16; 
         int result = first*10 + second; 
         if(result > 9) result--; 
         return result; 
 } 


static const long hextable[] = {
   [0 ... 255] = -1, // bit aligned access into this table is considerably
   ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, // faster for most modern processors,
   ['A'] = 10, 11, 12, 13, 14, 15,       // for the space conscious, reduce to
   ['a'] = 10, 11, 12, 13, 14, 15        // signed char.
};

long hexx(const char *hex ) {
   long ret = 0; 
   while (*hex && ret >= 0) {
      ret = (ret << 4) | hextable[*hex++];
   }
   return ret;
}

char* hexdec(const char *hex ) {
   char *p = malloc(sizeof(char)*32);
   sprintf(p,"%ld",hexx(hex));
   return p;
}

