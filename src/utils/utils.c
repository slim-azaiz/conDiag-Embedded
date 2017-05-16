#include "../../include/utils/utils.h"

//vars
char* usr;
char* pass;
char* oldPass;
char* newPass;
char* oldUser;
char* newUser;
char* finalPass;
char* finalUser;


//parse command of control
int parseCommand(char* string){
    cmd="";
    char* search = "/";
    char* str = "";
    str = strtok(string,search);
    str = strtok(NULL,search);
    cmd = str;
    return 0;
}
void parseParameterValue(char* string){
    Set *set = malloc(sizeof(Set));
    valueToSet="";
    parameterToSet="";
    char* search = "/";
    char* str = "";
    str = strtok(string,search);
    str = strtok(NULL,search);
    set->parameter = str;
    str = strtok(NULL,search);
    set->value = str;
    if(set->parameter!=NULL)
        parameterToSet = set->parameter;
    if(set->value!=NULL)
        valueToSet = set->value;
    free(set);
    printf("user = %s\n",parameterToSet);
    printf("pass = %s\n",valueToSet);
}


void parseUsernamePassword(char* string){
    Auth *auth = malloc(sizeof(Auth));
    usr="";
    pass="";
    char* search = "/";
    char* str = "";
    str = strtok(string,search);
    str = strtok(NULL,search);
    auth->username = str;
    str = strtok(NULL,search);
    auth->password = str;
    if(auth->username!=NULL)
        usr = auth->username;
    if(auth->password!=NULL)
        pass = auth->password;
    free(auth);
    printf("user = %s\n",usr);
    printf("pass = %s\n",pass);
}

//verify authentification
int authentificate(char* string ){
  parseUsernamePassword(string);

  FILE * ptrFile;
  FILE * ptrFile2;
  char line_user[256];
  char line_pass[256];
  int cur_line_user = 0;
  int cur_line_pass = 0;
  ptrFile=fopen(PASS_PATH,"rt");
  ptrFile2=fopen(USER_PATH,"rt");
  if (NULL==ptrFile) {
      printf("Corrupted file READ\n");
      return -1;
  }
  while(fgets(line_pass, sizeof line_pass, ptrFile)!= NULL ) 
  {
      if (cur_line_pass == 0) {
           line_pass[strlen(line_pass)-1] = '\0';
           finalPass = line_pass;
           printf("\nfinal_Pass=%s\n", finalPass);
           break;
      }
      cur_line_pass++;
  }
  fclose(ptrFile);

  while(fgets(line_user, sizeof line_user, ptrFile2)!= NULL ) 
  {
      if (cur_line_user == 0) {
           line_user[strlen(line_user)-1] = '\0';
           finalUser = line_user;
           printf("final_User=%s\n", finalUser);
           break;
      }
      cur_line_user++;
  }
  
  printf("L.User=%d\n",strlen(usr));
  printf("L.finalUser=%d\n",strlen(finalUser));
  printf("L.Pass=%d\n",strlen(pass));
  printf("L.finalPass=%d\n",strlen(finalPass));
  fclose(ptrFile2);
  
  if((strcmp(usr,finalUser)) || (strcmp(pass,finalPass))){
      return 0 ;
    
  } else
        return -1;
}

//parse new old username
void parseNewOldUsername(char* string){  
    NewOldUser *newOldUser = malloc(sizeof(NewOldUser));
    oldUser="";
    newUser="";
    char* search = "/";
    char* str = "";

    str = strtok(string,search);
    str = strtok(NULL,search);
    newOldUser->oldUser = str;
    str = strtok(NULL,search);
    newOldUser->newUser = str;
    if(newOldUser->oldUser!=NULL)
      oldUser = newOldUser->oldUser;
    if(newOldUser->newUser!=NULL)
      newUser = newOldUser->newUser;
    free(newOldUser);
}
//parse new old password
void parseNewOldPassword(char* string){  
    NewOldPass *newOldPass = malloc(sizeof(NewOldPass));
    oldPass="";
    newPass="";
    char* search = "/";
    char* str = "";

    str = strtok(string,search);
    str = strtok(NULL,search);
    newOldPass->oldPass = str;
    str = strtok(NULL,search);
    newOldPass->newPass = str;
    if(newOldPass->oldPass!=NULL)
      oldPass = newOldPass->oldPass;
    if(newOldPass->newPass!=NULL)
      newPass = newOldPass->newPass;
    free(newOldPass);
}
//parse new old password and rest the new one
int resetPassword(char* string ){
  parseNewOldPassword(string);
  FILE * ptrFile;
  char line[40];
  int cur_line = 0;
  ptrFile=fopen(PASS_PATH,"r");
  if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }
  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 0) {
           line[strlen(line)-1] = '\0';
           finalPass = line;
           printf(" finalPass=%s \n", finalPass);
           break;      
      }
        cur_line++;
  }
  fclose(ptrFile);
  printf("oldPass=%s\n",oldPass);
  printf("newPass=%s\n",newPass);
  printf("L.new=%d\n",strlen(newPass));
  printf("oldPass=%d\n",strlen(oldPass));
  printf("finalPass=%d\n",strlen(finalPass));
 
  if((!strcmp(oldPass,finalPass))){
      FILE * ptrw;
      ptrw=fopen(PASS_PATH,"w+");
      printf("L.new=%d\n",strlen(newPass));
      fprintf(ptrw,"%s\n\r",newPass);

      fclose(ptrw);
      return 0 ;
  } else{
      printf("ERROR\n");
     // free(finalUser); 
      return -1;
    }
}
//parse new old usernme and reset the new one
int resetUsername(char* string ){
  parseNewOldUsername(string);
  FILE * ptrFile;
  char line[40];
  int cur_line = 0;
  ptrFile=fopen(USER_PATH,"r");
  if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }
  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 0) {
           line[strlen(line)-1] = '\0';
           finalUser = line;
           printf(" finalUser=%s \n", finalUser);
           break;      
      }
        cur_line++;
  }
  fclose(ptrFile);
  printf("oldUser=%s\n",oldUser);
  printf("newUser=%s\n",newUser);
  printf("L.new=%d\n",strlen(newUser));
  printf("oldUser=%d\n",strlen(oldUser));
  printf("finalUser=%d\n",strlen(finalUser));
 
  if((!strcmp(oldUser,finalUser))){
      FILE * ptrw;
      ptrw=fopen(USER_PATH,"w+");
      printf("L.new=%d\n",strlen(newUser));
      fprintf(ptrw,"%s\n\r",newUser);

      fclose(ptrw);
      return 0 ;
  } else{
      printf("ERROR\n");
     // free(finalUser); 
      return -1;
    }
}

//convert mg_str to char *
char* mg_str2pTEXT(struct mg_str *mgstr)
{
    char* text = (char*) malloc(mgstr->len + 1);
    strncpy(text, mgstr->p, mgstr->len);
    text[mgstr->len] = '\0';
    return text;
}
