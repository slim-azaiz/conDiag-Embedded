#include "../../include/data/conditional_access_data.h"

void destroy_conditional_access_data()
{
	
}

void create_conditional_access_data(Conditional_access_data* conditional_access_data)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
   
    set_method(data,NAGRA_SERIAL_NUMBER);
    conditional_access_data->Nagra_Serial_Number = get_method_value_by_array(get_method(data),30);
    set_method(data,CA_PROVIDER_NAME);
    conditional_access_data->CA_Provider_Name = get_method_value_by_string(get_method(data));

    destroy_get_data();
    free(data);
}


