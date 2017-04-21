#include "../../include/utils/utils.h"


//vars
char* usr="";
char* pass="";
char* oldPass="";
char* newPass="";
char* finalPass="";
char* finalUser="";
//write new password in file
int modifyPass(char* password){
    FILE * ptrFile;
    
    ptrFile=fopen("/MY_PASSWD","w+");
    if (NULL==ptrFile) {
		printf("Corrupted file \n");
		return -1;
	}
    fprintf(ptrFile,"%s",password);
    fclose(ptrFile);
    return 1;
}
//read username from file
int readUsername(){
    FILE * ptrFile;
    char line[40];
	int cur_line = 0;
    finalUser =""; 
    ptrFile=fopen("/MY_PASSWD","r");
    if (NULL==ptrFile) {
		printf("Corrupted file \n");
		return -1;
	}
    while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
    {
        if (cur_line == 0) {
           // line[strlen(line)-1] = '\0';
              finalUser = line;
              printf(" finalUser=%s \n", finalUser);
           //  sprintf(finalPass,"%s",line);
        }
        cur_line++;
    }
    fclose(ptrFile);
    return 1;
}
//read password from file
int readPassword(){
    FILE * ptrFile;
    char line[40];
	int cur_line = 0;
    finalPass =""; 
    ptrFile=fopen("/MY_PASSWD","r");
    if (NULL==ptrFile) {
		printf("Corrupted file \n");
		return -1;
	}
    while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
    {
        if (cur_line == 1) {
           // line[strlen(line)-1] = '\0';
              finalPass = line;
              printf(" finalPass=%s \n", finalPass);
           //  sprintf(finalPass,"%s",line);
        }
        cur_line++;
    }
    fclose(ptrFile);
    return 1;
}
//parse command of control
int parseCommand(char* string){
    usr="";
    pass="";
    cmd="";
    char* search = "/";
    char* str = "";
    str = strtok(string,search);
    str = strtok(NULL,search);
    cmd = str;
    return 0;
}
//parse username and password from url 
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
  FILE * ptrFile;
  char line[40];
  int cur_line = 0;
  ptrFile=fopen("/MY_PASSWD","r");
 if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }
  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 0) {
          // line[strlen(line)-1] = '\0';
           finalPass = line;
           printf(" finalPass=%s \n", finalPass);
           //  sprintf(finalPass,"%s",line);
             }
        cur_line++;
  }
  fclose(ptrFile);
   // if((strcmp(usr,USERNAME)) && (strcmp(pass,finalPass)))
    
    printf("username= %s\n",usr);
    printf("password= %s\n",pass);
  if((strcmp(usr,USERNAME)))
        return 1 ;
      else
        return -1;
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
  ptrFile=fopen("/MY_PASSWD","r");
  if (NULL==ptrFile) {
      printf("Corrupted file \n");
      return -1;
  }
  while(fgets(line,31,ptrFile)!= NULL ) /* read a line */
  {
      if (cur_line == 0) {
          // line[strlen(line)-1] = '\0';
           finalPass = line;
           printf(" finalPass=%s \n", finalPass);
           //  sprintf(finalPass,"%s",line);
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
     // free(finalPass);
    printf("WHY\n");  
    FILE * ptrFile;
    
    ptrFile=fopen("/MY_PASSWD","w+");
    if (NULL==ptrFile) {
		printf("Corrupted file \n");
		return -1;
	}
    
    fprintf(ptrFile,"%s",newPass);
    fclose(ptrFile);
    printf("finalPasAfetr=%s\n",finalPass);  
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


