#include "../../include/data/control_data.h"
void destroy_control_data()
{
	
}

int create_control_data(Control_data* control_data,char* cmd)
{
    int result;
    Set_data *data = malloc(sizeof(Set_data));
    create_set_data();
    
    // #define NEC_STANBY_KEY_EVENT 0x708b3085
    set_method_value(data,SET_IR_INPUT_ID,cmd);
    //set_method_value(data,SET_NETWORK_ID,"standby");
    result = update_method_value(data->method, data->value);
    control_data->code = result;
    destroy_set_data();
    free(data);
    if(result == SET_DATA_ERROR)
    {
		return result;
	}
    return result;

}
