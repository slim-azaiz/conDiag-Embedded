#include "../../include/data/loader_data.h"
void destroy_loader_data()
{
	
}

void create_loader_data(Loader_data* loader_data)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();

    set_method(data,BOOT_LOADER_CRC);
    loader_data->boot_loader_crc = get_method_value_by_string(get_method(data));
    set_method(data,BOOTLOADER_VERSION);
    loader_data->boot_loader_version = get_method_value_by_array(get_method(data),5);
    
    destroy_get_data();
    free(data);
}

