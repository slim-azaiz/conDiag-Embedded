#include "../../include/data/set_parametres.h"
void destroy_set_parametres()
{
	
}

int create_set_parametres(Set_parametres* set_parametres,char* cmd)
{
    int result;
    Set_data *data = malloc(sizeof(Set_data));
    create_set_data();
    
    set_method_value(data,SET_NETWORK_ID,cmd);
    result = update_method_value(data->method, data->value);
    set_parametres->code = result;
    destroy_set_data();
    free(data);
    if(result == SET_DATA_ERROR)
    {
		return result;
	}
    return result;

}
