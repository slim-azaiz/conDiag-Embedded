// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved

#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"

#include "../include/data/all_parametres.h"
#include "../include/data/dynamic_parametres.h"
#include "../include/data/control_data.h"
#include "../include/data/set_parametres.h"
#include "../include/mongoose/mongoose.h"
#include "../include/cjson/cJSON.h"

#include "string.h"
#include <stdio.h>

#define USERNAME "root"
#define PASSWORD "root"

typedef struct Auth{
    char* username;
    char* password;
}Auth;

typedef struct NewOldPass{
    char* oldPass;
    char* newPass;
}NewOldPass;


char* usr="";
char* pass="";
char* oldPass="";
char* newPass="";
char* cmd="";
char* finalPass="";
char* finalUser="";
cJSON *objects[1];


//static
static const char* s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static All_parametres *all_parametres;
static Dynamic_parametres *dynamic_parametres;
static Control_data *control_data;
static Set_parametres *set_parametres;

char* json(int nb,int index){
    int i;
    cJSON *root = cJSON_CreateArray();
    for (i = 0; i < nb; i++){
        cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        cJSON_AddStringToObject(objects[i], "value",all_parametres->members[i+index][0]);
        cJSON_AddStringToObject(objects[i], "parameter",all_parametres->members[i+index][1]);
    }
   
     return cJSON_Print(root);
}
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
//parse command
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
  printf("username =%s\n",usr);
  printf("password =%s\n",pass);

  //if((strcmp(usr,USERNAME))&&(strcmp(pass,finalPass)))
  if((strcmp(pass,finalPass)))
        return 0 ;
      else
        return -1;
}

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
           //line[strlen(line)-1] = '\0';
           finalPass = line;
           printf(" finalPass=%s \n", finalPass);
             sprintf(finalPass,"%s",line);
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


char* mg_str2pTEXT(struct mg_str *mgstr)
{
    char* text = (char*) malloc(mgstr->len + 1);
    strncpy(text, mgstr->p, mgstr->len);
    text[mgstr->len] = '\0';
    return text;
}


//my event handler
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct http_message *hm = (struct http_message *) p;
  if (ev == MG_EV_HTTP_REQUEST) {
    
    //authentification
    if (strstr(mg_str2pTEXT(&hm->uri),"/authentificate")) {
        printf("result = %d",authentificate(mg_str2pTEXT(&hm->uri)));
      if(authentificate(mg_str2pTEXT(&hm->uri))){
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        printf("%s\nsuccess\n",mg_str2pTEXT(&hm->uri));
        mg_printf_http_chunk(nc, "SUCCESS");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        printf("%s\nERROR\n",mg_str2pTEXT(&hm->uri));
        mg_printf_http_chunk(nc, "WRONG USERNAME OR PASSWORD");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    }
    //resetPassword
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetPassword")) {
      if(!resetPassword(mg_str2pTEXT(&hm->uri))){
      
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "SUCCESS");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG OLD PASSWORD");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    }
    //control
    else if (strstr(mg_str2pTEXT(&hm->uri),"/control")) {
      if(!parseCommand(mg_str2pTEXT(&hm->uri))){
        //execute command
        control_data = malloc(sizeof(Control_data));
        int ret = create_control_data(control_data,cmd);
       
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "%s CLICKED \nresultat=%d",cmd,ret);
        printf("\n%s ",mg_str2pTEXT(&hm->uri));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG COMMAND");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    //set networkID
    } 
    else if (strstr(mg_str2pTEXT(&hm->uri),"/networkID")) {
      if(!parseCommand(mg_str2pTEXT(&hm->uri))){
        //execute command
        set_parametres = malloc(sizeof(Set_parametres));
        int ret = create_set_parametres(set_parametres,cmd);
       
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "%s CLICKED \nresultat=%d",cmd,ret);
        printf("\n%s ",mg_str2pTEXT(&hm->uri));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG COMMAND");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    }
    //diagnostic static parametres
    else if (strstr(mg_str2pTEXT(&hm->uri),"diagnostic")) {
        //all parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"diagnostics\":%s}\n",json(43,0));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"identification")) {
        // stb_identification      
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"identification\":%s}\n",json(10,0));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"conditionalAccess")) {
        //conditional_access
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"conditional\":%s}\n",json(2,10));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"memory")) {
        //memoire_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"memory\":%s}\n",json(4,14));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"loader")) {
        //loader_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"loader\":%s}\n",json(2,12));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"software")) {
        //software_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"software\":%s}\n",json(4,26));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"network")) {
        //network_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"network\":%s}\n",json(8,18));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"sysInfo")) {
        //sys_info 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"sysInfo\":%s}\n",json(13,30));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }else if (strstr(mg_str2pTEXT(&hm->uri),"realTime")) {
      // dynamic parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        dynamic_parametres = malloc(sizeof(Dynamic_parametres));
        create_dynamic_parametres(dynamic_parametres); 
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 6; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
            cJSON_AddStringToObject(objects[i], "value",dynamic_parametres->members[i][0]);
            cJSON_AddStringToObject(objects[i], "parameter",dynamic_parametres->members[i][1]);
        }
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"realTime\":%s}\n",result);
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }        
       mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
  }
}


//main
int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  
  all_parametres = malloc(sizeof(All_parametres));
  create_all_parametres(all_parametres);

  mg_mgr_init(&mgr, NULL);
  printf("Starting web server on port %s\n", s_http_port);

  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    printf("Failed to create listener\n");
    return 1;
  }

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(nc);
  //s_http_server_opts.document_root = ".";  // Serve current directory
  //s_http_server_opts.enable_directory_listing = "yes";

  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return 0;
}
