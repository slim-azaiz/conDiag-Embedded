#ifndef CONTROL_DATA_H
#define CONTROL_DATA_H

#include "get_data.h"
#include "set_data.h"
 //iir_input
#define NEC_STANBY_KEY_EVENT 0x708b3085

typedef struct Control_data{
    int code;
}Control_data;

int create_control_data(Control_data * conrol_data,char* cmd);
void destroy_control_data();
int setCode(char* code);
#endif //CONTROL_DATA_H
