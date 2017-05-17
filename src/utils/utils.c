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
int parseCommand(char* uri,char* control_key){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    control_key = str;
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
void parseUsernamePassword(char* uri,Auth *auth){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    auth->username = str;
    str = strtok(NULL,search);
    auth->password = str;
    printf("user = %s\n",auth->username);
    printf("pass = %s\n",auth->password);
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
void parseNewOldParameter(char* uri,NewOldParameter *newOldParameter){
    char* search = "/";
    char* str = "";
    str = strtok(uri,search);
    str = strtok(NULL,search);
    newOldParameter->oldParameter = str;
    str = strtok(NULL,search);
    newOldParameter->newParameter = str;
    printf("oldParameter = %s\n",newOldParameter->oldParameter);
    printf("newParameter = %s\n",newOldParameter->newParameter);
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
int getUsernamePassword(Auth* auth){
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
           auth->password = line_pass;
           printf("\nfinal_Pass=%s\n", auth->password);
           break;
      }
      cur_line_pass++;
  }
  fclose(ptrFileUsername);

  while(fgets(line_user, sizeof line_user, ptrFilePassword)!= NULL ) 
  {
      if (cur_line_user == 0) {
           line_user[strlen(line_user)-1] = '\0';
           auth->username = line_user;
           printf("final_User=%s\n", auth->username);
           break;
      }
      cur_line_user++;
  }
  
  printf("L.finalUser=%d\n",strlen(auth->username));
  printf("L.finalPass=%d\n",strlen(auth->password));
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
int authentificate(Auth* auth){
    Auth* finalAuth = malloc(sizeof(Auth));
    getUsernamePassword(finalAuth);
    if((strcmp(auth->username,finalAuth->username)) || (strcmp(auth->password,finalAuth->password))){
        return 0 ;
    } else
        return -1;
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
int resetPassword(NewOldParameter* newOldPassword){
    Auth* finalAuth = malloc(sizeof(Auth));
    getUsernamePassword(finalAuth);
 
    if((!strcmp(newOldPassword->oldParameter,finalAuth->password))){
        FILE * ptrw;
        ptrw=fopen(PASS_PATH,"w+");
        fprintf(ptrw,"%s\n\r",newOldPassword->newParameter);
        fclose(ptrw);
        free(finalAuth);
        return 0 ;
    } else{
        free(finalAuth);
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
int resetUsername(NewOldParameter* newOldUsername){
    Auth* finalAuth = malloc(sizeof(Auth));
    getUsernamePassword(finalAuth);
    if((!strcmp(newOldUsername->oldParameter,finalAuth->username))){
        FILE * ptrw;
        ptrw=fopen(USER_PATH,"w+");
        fprintf(ptrw,"%s\n\r",newOldUsername->newParameter);
        fclose(ptrw);
        free(finalAuth);
        return 0 ;
    } else{
        printf("ERROR\n");
        free(finalAuth);
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
