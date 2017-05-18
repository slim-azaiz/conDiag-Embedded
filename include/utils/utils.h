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
#define RESULT_SUCCESS						0
#define RESULT_ERROR						(-1)
#define MAX_USERNAME_PASSWORD_LENGTH		20
/**********************************************************************************
*						              STRUCTURES
**********************************************************************************/
typedef struct Auth{
    char username[20];
    char password[20];
}Auth;
typedef struct NewOldParameter{
    char* oldParameter[20];
    char* newParameter(20];
}NewOldParameter;


/**********************************************************************************
*						              FUNCTIONS
**********************************************************************************/
int authentificate(Auth* auth);
char* mg_str2pTEXT(struct mg_str *mgstr);
void parseCommand(char* uri,char* control_key);
void parseNewOldParameter(char* uri,NewOldParameter* newOldPassword);
void parseUsernamePassword(char* uri, Auth* auth);
int resetPassword(NewOldParameter*);
int resetUsername(NewOldParameter*);


#endif //UTILS_H
