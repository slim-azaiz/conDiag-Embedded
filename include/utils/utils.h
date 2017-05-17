#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include "data/dynamic_parametres.h"
#include "data/set_data.h"
#include "mongoose/mongoose.h"
#include "cjson/cJSON.h"
#include "data/all_parametres.h"
/**********************************************************************************
*						              DEFINES
**********************************************************************************/
#define PASS_PATH "/volatile/sagem/diagnostic/PASSWORD" 
#define USER_PATH "/volatile/sagem/diagnostic/USERNAME"
/**********************************************************************************
*						              STRUCTURES
**********************************************************************************/
typedef struct Auth{
    char* username;
    char* password;
}Auth;
typedef struct NewOldParameter{
    char* oldParameter;
    char* newParameter;
}NewOldParameter;


/**********************************************************************************
*						              FUNCTIONS
**********************************************************************************/
int authentificate(Auth* auth);
char* mg_str2pTEXT(struct mg_str *mgstr);
int parseCommand(char* uri,char* control_key);
void parseNewOldParameter(char* uri,NewOldParameter* newOldPassword);
void parseUsernamePassword(char* uri, Auth* auth);
int resetPassword(NewOldParameter*);
int resetUsername(NewOldParameter*);


#endif //UTILS_H
