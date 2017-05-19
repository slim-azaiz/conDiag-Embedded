#include "utils/utils.h"


/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : parseCommand
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : parse command of control 
 * Return type   : int
 * Argument      : control_key: Out
                   uri:In
                   
 **********************************************************************/
int parseCommand(char* uri,char** control_key){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    *control_key =strdup(str);
    return 0;
}

/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : parseUsernamePassword
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : parse the username and password from uri 
 * Return type   : void
 * Argument      : auth: Out
                   uri:In
                   
 **********************************************************************/
void parseUsernamePassword(char* uri,char** username, char** password){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    *username = strdup(str);
    str = strtok(NULL,search);
    *password = strdup(str);
    printf("user = %s\n",username);
    printf("pass = %s\n",password);
    printf("L.User=%d\n",strlen(username));
    printf("L.Pass=%d\n",strlen(password));
}
/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : parseNewOldParameter
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : parse the arguments posted from uri 
 * Return type   : void
 * Argument      : newOldParameter: Out
                   uri:In
                   
 **********************************************************************/
void parseNewOldParameter(char* uri,char** oldParameter,char** newParameter){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    *oldParameter = strdup(str);
    str = strtok(NULL,search);
    *newParameter = strdup(str);
    printf("oldParameter = %s\n",oldParameter);
    printf("newParameter = %s\n",newParameter);
}
/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : getUsernamePassword
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : get username and password from USERNAME and PASSWORD 
 * Return type   : int
 * Argument      : auth: Out
                   
 **********************************************************************/
int getUsernamePassword(char** username, char** password){
  FILE * ptrFileUsername;
  FILE * ptrFilePassword;
  char line_user[256];
  char line_pass[256];
  int cur_line_user = 0;
  int cur_line_pass = 0;
  ptrFileUsername=fopen(PASS_PATH,"rt");
  ptrFilePassword=fopen(USER_PATH,"rt");
  if (NULL==ptrFileUsername) {
      printf("Corrupted file READ\n");
      return -1;
  }
  while(fgets(line_pass, sizeof line_pass, ptrFileUsername)!= NULL ) 
  {
      if (cur_line_pass == 0) {
           line_pass[strlen(line_pass)-1] = '\0';
           *password = strdup(line_pass);
           printf("\nfinal_Pass=%s\n", password);
           break;
      }
      cur_line_pass++;
  }
  fclose(ptrFileUsername);

  while(fgets(line_user, sizeof line_user, ptrFilePassword)!= NULL ) 
  {
      if (cur_line_user == 0) {
           line_user[strlen(line_user)-1] = '\0';
           *username =strdup(line_user);
           printf("final_User=%s\n", username);
           break;
      }
      cur_line_user++;
  }
  
  printf("L.finalUser=%d\n",strlen(username));
  printf("L.finalPass=%d\n",strlen(password));
  fclose(ptrFilePassword);
  return 0 ;
    
}

/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : authentificate
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : verify authentification 
 * Return type   : int
 * Argument      : auth: Out
                   
 **********************************************************************/
int authentificate(char* username, char* password){
    char* finalUsername;
    char* finalPassword;
    getUsernamePassword(&finalUsername,&finalPassword);
    printf("finalUsername = %s\n",finalUsername);
    printf("finalPassword = %s\n",finalPassword);
    printf("Password = %s\n",password);
    printf("Username = %s\n",username);
    if((strcmp(username,finalUsername)) || (strcmp(password,finalPassword))){
        free(finalUsername);
        free(finalPassword);
        return 0 ;
    } else{
        free(finalUsername);
        free(finalPassword);
        return -1;
    }
}

/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : newOldPassword
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : parse new,old password and rest the new one 
 * Return type   : int
 * Argument      : newOldPassword: Out
                   
 **********************************************************************/
int resetPassword(char* oldPass,char* newPass){
    char* finalUsername;
    char* finalPassword;
    getUsernamePassword(&finalUsername,&finalPassword);
 
    if((!strcmp(oldPass,finalPassword))){
        FILE * ptrw;
        ptrw=fopen(PASS_PATH,"w+");
        fprintf(ptrw,"%s\n\r",oldPass);
        fclose(ptrw);
        free(finalUsername);
        free(finalPassword);
        return 0 ;
    } else{
        free(finalUsername);
        free(finalPassword);
        printf("ERROR\n");
        return -1;
    }
}
/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : resetUsername
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : parse new,old usernme and reset the new one
 * Return type   : int
 * Argument      : newOldUsername: Out
                   
 **********************************************************************/
int resetUsername(char* oldUser,char* newUser){
    char* finalUsername;
    char* finalPassword;
    getUsernamePassword(&finalUsername,&finalPassword);
    if((!strcmp(oldUser,finalUsername))){
        FILE * ptrw;
        ptrw=fopen(USER_PATH,"w+");
        fprintf(ptrw,"%s\n\r",newUser);
        fclose(ptrw);
        free(finalUsername);
        free(finalPassword);
        return 0 ;
    } else{
        printf("ERROR\n");
        free(finalUsername);
        free(finalPassword);
        return -1;
    }
}

/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : mg_str2pTEXT
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : convert mg_str to char * 
 * Return type   : char*
 * Argument      : mgstr:In
 **********************************************************************/

char* mg_str2pTEXT(struct mg_str *mgstr)
{
    char* text = (char*) malloc(mgstr->len + 1);
    strncpy(text, mgstr->p, mgstr->len);
    text[mgstr->len] = '\0';
    return text;
}
