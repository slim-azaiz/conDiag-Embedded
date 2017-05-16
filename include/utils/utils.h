#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include "data/all_parametres.h"
#include "data/dynamic_parametres.h"
#include "data/control_data.h"
#include "mongoose/mongoose.h"
#include "cjson/cJSON.h"
#include "data/set_parametres.h"

#define PASS_PATH "/volatile/sagem/diagnostic/PASSWORD" 
#define USER_PATH "/volatile/sagem/diagnostic/USERNAME"

//structures
typedef struct Auth{
    char* username;
    char* password;
}Auth;

/* Use only one structure definition and declare instead two struct variables (old and new) */
typedef struct NewOldPass{
    char* oldPass;
    char* newPass;
}NewOldPass;
typedef struct NewOldUser{
    char* oldUser;
    char* newUser;
}NewOldUser;

typedef struct Set{ //Set_parameter
    char* parameter;
    char* value;
}Set;

char* cmd;//control_key
char* valueToSet;// ??
char* parameterToSet;//???
//functions
int authentificate(char* string );
char* mg_str2pTEXT(struct mg_str *mgstr);
int modifyPass(char* password);
int parseCommand(char* string);
void parseNewOldPassword(char* string);
void parseUsernamePassword(char* string);
int resetPassword(char* string );
int resetUsername(char* string );

#endif //UTILS_H
