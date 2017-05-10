#include "../../include/data/control_data.h"
void destroy_control_data()
{
	
}

void create_control_data()
{
    Set_data *data = malloc(sizeof(Set_data));
    create_set_data();
    
    //set_method_value(data,SET_IR_INPUT_ID,cmd);
    //result = update_method_value(SET_IR_INPUT_ID, cmd);
   // destroy_set_data();
   // free(data);

}
