#include "../../include/data/memoire_data.h"#include <stdio.h>void destroy_memoire_data(){	}void create_memoire_data(Memoire_data* memoire_data){    Get_data *data = malloc(sizeof(Get_data));    create_get_data();      set_method(data,ADDRESSING_MEMORY);    memoire_data->addressing_memory = get_method_value_by_string(get_method(data));    set_method(data,MEMORY_BLOCK_STATUS);    memoire_data->memory_block_status = get_method_value_by_string(get_method(data));    set_method(data,USED_MEMORY);    memoire_data->used_memory = get_method_value_by_string(get_method(data));    set_method(data,TOTAL_MEMORY);    memoire_data->total_memory = get_method_value_by_string(get_method(data));        destroy_get_data();    free(data);}