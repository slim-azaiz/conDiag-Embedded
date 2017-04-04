#include "../../include/data/software_data.h"
#include <stdio.h>

void destroy_software_data()
{
	
}

void create_software_data(Software_data *software_data)
{
    Get_data *data = malloc(sizeof(Get_data));
    create_get_data();
	
	set_method(data,BOOTLOADER_VERSION);
	software_data->bootloader_version = get_method_value_by_array(get_method(data),5);
	set_method(data,TOTAL_SOFTWARE_UPDATES);
	software_data->total_software_updates = get_method_value_by_array(get_method(data),50);
	set_method(data,DATE_TIME_LAST_STB_SOFTWARE);
	software_data->date_time_last_stb_software= get_method_value_by_array(get_method(data),30);
	set_method(data,TIVO_SOFTWARE_NAME);
	software_data->tivo_software_name= get_method_value_by_array(get_method(data),40);

    destroy_get_data();
    free(data);
}

