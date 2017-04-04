#ifndef CONDITIONAL_ACCES_DATA_H
#define CONDITIONAL_ACCES_DATA_H
#include "get_data.h"

typedef struct Conditional_access_data
{
    char* Nagra_Serial_Number;   
    char* CA_Provider_Name;
}Conditional_access_data;


void create_Conditional_access_data(Conditional_access_data *Conditional_access_data);
void destroy_Conditional_access_data();



#endif // CONDITIONAL_ACCES_DATA_H
