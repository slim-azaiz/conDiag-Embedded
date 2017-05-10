#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include <stdio.h>

#include "../../include/data/all_parametres.h"
#include "../../include/data/dynamic_parametres.h"
#include "../../include/data/control_data.h"
#include "../../include/mongoose/mongoose.h"
#include "../../include/cjson/cJSON.h"
#include "../../include/data/set_parametres.h"

#define USERNAME "root"
#define PASSWORD "root"
#define FILE_PATH "/volatile/sagem/diagnostic/conDiagd.conf" 

//structures
typedef struct Auth{
    char* username;
    char* password;
}Auth;

typedef struct NewOldPass{
    char* oldPass;
    char* newPass;
}NewOldPass;

typedef struct NewOldUser{
    char* oldUser;
    char* newUser;
}NewOldUser;


char* cmd;
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
