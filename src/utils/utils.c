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
}

//verify authentification
int authentificate(char* string ){
  parseUsernamePassword(string);
  int iFileDescriptor = -1;
  iFileDescriptor = open(FILE_PATH,O_RDONLY, 0400);
  if(iFileDescriptor < 0) {
      printf("\nError Opening Default Diagnostic Conf File\n");
      return iFileDescriptor;
  }  
  
  FILE * ptrFile;
  FILE * ptrFile2;
  char line_user[256];
  char line_pass[256];
  int cur_line_user = 0;
  int cur_line_pass = 0;
  ptrFile=fopen(FILE_PATH,"rt");
  ptrFile2=fopen(FILE_PATH,"rt");
  if (NULL==ptrFile) {
      printf("Corrupted file READ\n");
      return -1;
  }
  while(fgets(line_pass, sizeof line_pass, ptrFile)!= NULL ) 
  {
      if (cur_line_pass == 1) {
           //line_pass[strlen(line_pass)-1] = '\0';
           finalPass = line_pass;
           printf(" finalPass=%s \n", finalPass);
           break;
      }
      cur_line_pass++;
  }
  fclose(ptrFile);
  while(fgets(line_user, sizeof line_user, ptrFile2)!= NULL ) 
  {
      if (cur_line_user == 0) {
           //line_user[strlen(line_user)-1] = '\0';
           finalUser = line_user;
           printf(" finalUser=%s \n", finalUser);
           break;
      }
      cur_line_user++;
  }
  
  printf("L.Users=%d\n",strlen(usr));
  printf("L.finalUser=%d\n",strlen(finalUser));
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
  printf("finalPassBefore=%s\n",finalPass);
  FILE * ptrFile;
  char line[40];
  int cur_line = 0;
  ptrFile=fopen(FILE_PATH,"r");
  if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }


  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 1) {
           line[strlen(line)] = '\0';
           finalPass = line;
           printf(" finalPass=%s \n", finalPass);
           break;      
      }
        cur_line++;
  }
  fclose(ptrFile);
  printf("finalPassBefore=%s\n",finalPass);
  printf("oldPass=%s\n",oldPass);
  printf("newPass=%s\n",newPass);
  printf("oldPass=%d\n",strlen(oldPass));
  printf("finalPass=%d\n",strlen(finalPass));
 


  if((!strcmp(oldPass,finalPass))){
    
      FILE * ptrFile2;
      char line_user[256];
      int cur_line_user = 0;
      ptrFile2=fopen(FILE_PATH,"rt");
    
      while(fgets(line_user, sizeof line_user, ptrFile2)!= NULL ) 
      {
          if (cur_line_user == 0) {
              line_user[strlen(line_user)] = '\0';
              finalUser = line_user;
              printf(" finalUser=%s \n", finalUser);
              break;
          }
          cur_line_user++;
      }
      fclose(ptrFile2);
      
      FILE * ptrw;
      ptrw=fopen(FILE_PATH,"w+");

      fprintf(ptrw,"%s\n%s",finalUser,newPass);
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
  ptrFile=fopen(FILE_PATH,"r");
  if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }
  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 0) {
      //     line[strlen(line)-1] = '\0';
           finalUser = line;
           //  sprintf(finalPass,"%s",line);
             }
        cur_line++;
  }
  fclose(ptrFile);
  
  if((!strcmp(oldUser,finalUser))){
      FILE * ptrFile;
      char line_pass[256];
      int cur_line_pass = 0;
      ptrFile=fopen(FILE_PATH,"rt");
    
      while(fgets(line_pass, sizeof line_pass, ptrFile)!= NULL ) 
      {
          if (cur_line_pass == 0) {
              //line_pass[strlen(line_pass)-1] = '\0';
              finalPass = line_pass;
              printf(" finalPass=%s \n", finalPass);
              break;
          }
          cur_line_pass++;
      }
      fclose(ptrFile);
      
      FILE * ptrw;
      ptrw=fopen(FILE_PATH,"w+");

      //newUser[strlen(newUser)+1] = '\0';
      fprintf(ptrw,"%s%s",newUser,finalPass);
      fclose(ptrw);
      printf("finalPAfetr=%s\n",finalPass);  
      return 0 ;
  } else{
      printf("ERROR\n");
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


