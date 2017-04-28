#ifndef SET_PARAMETRES_H
#define SET_PARAMETRES_H

#include "get_data.h"
#include "set_data.h"

typedef struct Set_parametres{
    int code;
}Set_parametres;

int create_set_parametres(Set_parametres * set_parametres,char* param);
void destroy_set_parametres();
int setCode(char* code);
#endif //SET_PARAMETRES_H
