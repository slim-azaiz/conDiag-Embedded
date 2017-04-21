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

#define USERNAME "root"
#define PASSWORD "root"

//structures
typedef struct Auth{
    char* username;
    char* password;
}Auth;

typedef struct NewOldPass{
    char* oldPass;
    char* newPass;
}NewOldPass;



char* cmd;
//functions
int authentificate(char* string );
char* mg_str2pTEXT(struct mg_str *mgstr);
int modifyPass(char* password);
int parseCommand(char* string);
void parseNewOldPassword(char* string);
void parseUsernamePassword(char* string);
int readPassword();
int readUsername();
int resetPassword(char* string );

#endif //UTILS_H
