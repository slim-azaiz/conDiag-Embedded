// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved

#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"

#include "../include/data/all_parametres.h"
#include "../include/data/dynamic_parametres.h"
#include "../include/data/control_data.h"
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

cJSON *objects[1];
//static
static const char* s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static All_parametres *all_parametres;
static Dynamic_parametres *dynamic_parametres;
static Control_data *control_data;

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
    }
    //diagnostic static parametres
    else if (strstr(mg_str2pTEXT(&hm->uri),"diagnostic")) {
        //all parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
       

        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 40; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }


        //VALUE
        //stb_identification      
        cJSON_AddStringToObject(objects[0], "value",all_parametres->serial_number);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->nagra_serial_number);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->model);
        cJSON_AddStringToObject(objects[3], "value",all_parametres->stb_mac_address);
        cJSON_AddStringToObject(objects[4], "value",all_parametres->ethernet_mac_address);
        cJSON_AddStringToObject(objects[5], "value",all_parametres->firmware_version);
        cJSON_AddStringToObject(objects[6], "value",all_parametres->network_id);
        cJSON_AddStringToObject(objects[7], "value",all_parametres->manufacturer);
        //conditional_access
        cJSON_AddStringToObject(objects[8], "value",all_parametres->Nagra_Serial_Number);
        cJSON_AddStringToObject(objects[9], "value",all_parametres->CA_Provider_Name);
        //loader_data
        cJSON_AddStringToObject(objects[10], "value",all_parametres->boot_loader_version);
        cJSON_AddStringToObject(objects[11], "value",all_parametres->boot_loader_crc);
        //memoire_data
        cJSON_AddStringToObject(objects[12], "value",all_parametres->memory_block_status);
        cJSON_AddStringToObject(objects[13], "value",all_parametres->used_memory);
        cJSON_AddStringToObject(objects[14], "value",all_parametres->total_memory);
        cJSON_AddStringToObject(objects[15], "value",all_parametres->addressing_memory);
        //network_data
        cJSON_AddStringToObject(objects[16], "value",all_parametres->stb_serial_number);
        cJSON_AddStringToObject(objects[17], "value",all_parametres->manufacturer);
        cJSON_AddStringToObject(objects[18], "value",all_parametres->stb_ip_address);
        cJSON_AddStringToObject(objects[19], "value",all_parametres->stb_mac_ethernet);
        cJSON_AddStringToObject(objects[20], "value",all_parametres->stb_ethernet_port_status);
        cJSON_AddStringToObject(objects[21], "value",all_parametres->dns_serverII);
        cJSON_AddStringToObject(objects[22], "value",all_parametres->stb_ip_default_gateway);
        cJSON_AddStringToObject(objects[23], "value",all_parametres->stb_subnet_mask);
        //software_data
        cJSON_AddStringToObject(objects[24], "value",all_parametres->tivo_software_name);
        cJSON_AddStringToObject(objects[25], "value",all_parametres->date_time_last_stb_software);
        cJSON_AddStringToObject(objects[26], "value",all_parametres->total_software_updates);
        //sys_info 
        cJSON_AddStringToObject(objects[27], "value",all_parametres->IR_Input_Status);
        cJSON_AddStringToObject(objects[28], "value",all_parametres->Internal_Temperature);
        cJSON_AddStringToObject(objects[29], "value",all_parametres->CPU_Utilisation);
        cJSON_AddStringToObject(objects[30], "value",all_parametres->HDMI_Port_Status);
        cJSON_AddStringToObject(objects[31], "value",all_parametres->Video_Resolution);
        cJSON_AddStringToObject(objects[32], "value",all_parametres->Video_Aspect_Ratio);
        cJSON_AddStringToObject(objects[33], "value",all_parametres->Video_Format);
        cJSON_AddStringToObject(objects[34], "value",all_parametres->Diagnostics_Pages_Language);
        cJSON_AddStringToObject(objects[35], "value",all_parametres->Audio_Setup);
        cJSON_AddStringToObject(objects[36], "value",all_parametres->STB_Lifetime);
        cJSON_AddStringToObject(objects[37], "value",all_parametres->STB_totalPowerOff);
        cJSON_AddStringToObject(objects[38], "value",all_parametres->Time_since_last_STB_boot_up);
        cJSON_AddStringToObject(objects[39], "value",all_parametres->Total_STB_Reboot);
       
        //parameter
        //stb_identification      
        cJSON_AddStringToObject(objects[0], "parameter","Serial number");
        cJSON_AddStringToObject(objects[1], "parameter","Nagra serial number");
        cJSON_AddStringToObject(objects[2], "parameter","Model");
        cJSON_AddStringToObject(objects[3], "parameter","Stb mac address");
        cJSON_AddStringToObject(objects[4], "parameter","Ethernet mac address");
        cJSON_AddStringToObject(objects[5], "parameter","Firmware version");
        cJSON_AddStringToObject(objects[6], "parameter","Network id");
        cJSON_AddStringToObject(objects[7], "parameter","Manufacturer");
        //conditional_access
        cJSON_AddStringToObject(objects[8], "parameter","Nagra Serial Number");
        cJSON_AddStringToObject(objects[9], "parameter","CA provider name");
        //loader_data
        cJSON_AddStringToObject(objects[10], "parameter","Boot loader version");
        cJSON_AddStringToObject(objects[11], "parameter","Boot loader crc");
        //memoire_data
        cJSON_AddStringToObject(objects[12], "parameter","Memory block status");
        cJSON_AddStringToObject(objects[13], "parameter","Used memory");
        cJSON_AddStringToObject(objects[14], "parameter","Total memory");
        cJSON_AddStringToObject(objects[15], "parameter","Addressing memory");
        //network_data
        cJSON_AddStringToObject(objects[16], "parameter","STB serial number");
        cJSON_AddStringToObject(objects[17], "parameter","Manufacturer");
        cJSON_AddStringToObject(objects[18], "parameter","STB ip address");
        cJSON_AddStringToObject(objects[19], "parameter","STB mac ethernet");
        cJSON_AddStringToObject(objects[20], "parameter","STB ethernet port status");
        cJSON_AddStringToObject(objects[21], "parameter","DNS serverII");
        cJSON_AddStringToObject(objects[22], "parameter","STB ip default gateway");
        cJSON_AddStringToObject(objects[23], "parameter","STB subnet mask");
        //software_data
        cJSON_AddStringToObject(objects[24], "parameter","TiVo software name");
        cJSON_AddStringToObject(objects[25], "parameter","Date time last STB software");
        cJSON_AddStringToObject(objects[26], "parameter","Total software updates");
        //sys_info 
        cJSON_AddStringToObject(objects[27], "parameter","IR Input Status");
        cJSON_AddStringToObject(objects[28], "parameter","Internal Temperature");
        cJSON_AddStringToObject(objects[29], "parameter","CPU utilisation");
        cJSON_AddStringToObject(objects[30], "parameter","HDMI Port Status");
        cJSON_AddStringToObject(objects[31], "parameter","Video Resolution");
        cJSON_AddStringToObject(objects[32], "parameter","Video Aspect_Ratio");
        cJSON_AddStringToObject(objects[33], "parameter","Video Format");
        cJSON_AddStringToObject(objects[34], "parameter","Diagnostics Pages Language");
        cJSON_AddStringToObject(objects[35], "parameter","Audio Setup");
        cJSON_AddStringToObject(objects[36], "parameter","STB Lifetime");
        cJSON_AddStringToObject(objects[37], "parameter","STB totalPowerOff");
        cJSON_AddStringToObject(objects[38], "parameter","Time since last STB boot_up");
        cJSON_AddStringToObject(objects[39], "parameter","Total STB_Reboot");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"diagnostics\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"identification")) {
        //all parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 8; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //stb_identification      
        cJSON_AddStringToObject(objects[0], "value",all_parametres->serial_number);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->nagra_serial_number);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->model);
        cJSON_AddStringToObject(objects[3], "value",all_parametres->stb_mac_address);
        cJSON_AddStringToObject(objects[4], "value",all_parametres->ethernet_mac_address);
        cJSON_AddStringToObject(objects[5], "value",all_parametres->firmware_version);
        cJSON_AddStringToObject(objects[6], "value",all_parametres->network_id);
        cJSON_AddStringToObject(objects[7], "value",all_parametres->manufacturer);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","Serial number");
        cJSON_AddStringToObject(objects[1], "parameter","Nagra serial number");
        cJSON_AddStringToObject(objects[2], "parameter","Model");
        cJSON_AddStringToObject(objects[3], "parameter","STB mac address");
        cJSON_AddStringToObject(objects[4], "parameter","Ethernet mac address");
        cJSON_AddStringToObject(objects[5], "parameter","Firmware version");
        cJSON_AddStringToObject(objects[6], "parameter","Network ID");
        cJSON_AddStringToObject(objects[7], "parameter","Manufacturer");
       
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"identification\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"conditionalAccess")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 2; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //conditional_access
        cJSON_AddStringToObject(objects[0], "value",all_parametres->Nagra_Serial_Number);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->CA_Provider_Name);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","Nagra serial number");
        cJSON_AddStringToObject(objects[1], "parameter","CA provider name");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"conditional\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"memory")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 4; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //memoire_data
        cJSON_AddStringToObject(objects[0], "value",all_parametres->memory_block_status);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->used_memory);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->total_memory);
        cJSON_AddStringToObject(objects[3], "value",all_parametres->addressing_memory);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","Memory block status");
        cJSON_AddStringToObject(objects[1], "parameter","Used memory");
        cJSON_AddStringToObject(objects[2], "parameter","Total memory");
        cJSON_AddStringToObject(objects[3], "parameter","Addressing memory");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"memory\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */

     }else if (strstr(mg_str2pTEXT(&hm->uri),"loader")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 2; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //loader_data
        cJSON_AddStringToObject(objects[0], "value",all_parametres->boot_loader_version);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->boot_loader_crc);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","Boot loader version");
        cJSON_AddStringToObject(objects[1], "parameter","Boot loader crc");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"loader\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"software")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 3; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //software_data
        cJSON_AddStringToObject(objects[0], "value",all_parametres->tivo_software_name);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->date_time_last_stb_software);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->total_software_updates);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","TiVo software name");
        cJSON_AddStringToObject(objects[1], "parameter","Date/time last STB software");
        cJSON_AddStringToObject(objects[2], "parameter","Total software updates");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"software\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"network")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 8; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //network_data
        cJSON_AddStringToObject(objects[0], "value",all_parametres->stb_serial_number);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->manufacturer);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->stb_ip_address);
        cJSON_AddStringToObject(objects[3], "value",all_parametres->stb_mac_ethernet);
        cJSON_AddStringToObject(objects[4], "value",all_parametres->stb_ethernet_port_status);
        cJSON_AddStringToObject(objects[5], "value",all_parametres->dns_serverII);
        cJSON_AddStringToObject(objects[6], "value",all_parametres->stb_ip_default_gateway);
        cJSON_AddStringToObject(objects[7], "value",all_parametres->stb_subnet_mask);
        //parameter      
        cJSON_AddStringToObject(objects[0],  "parameter","STB serial number");
        cJSON_AddStringToObject(objects[1],  "parameter","Manufacturer");
        cJSON_AddStringToObject(objects[2],  "parameter","STB ip address");
        cJSON_AddStringToObject(objects[3],  "parameter","STB mac ethernet");
        cJSON_AddStringToObject(objects[4],  "parameter","STB ethernet port status");
        cJSON_AddStringToObject(objects[5],  "parameter","DNS serverII");
        cJSON_AddStringToObject(objects[6],  "parameter","STB_ip default gateway");
        cJSON_AddStringToObject(objects[7],  "parameter","STB subnet mask");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"network\":%s}\n",result);
                                       
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"sysInfo")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 13; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        //sys_info 
        cJSON_AddStringToObject(objects[0], "value",all_parametres->IR_Input_Status);
        cJSON_AddStringToObject(objects[1], "value",all_parametres->Internal_Temperature);
        cJSON_AddStringToObject(objects[2], "value",all_parametres->CPU_Utilisation);
        cJSON_AddStringToObject(objects[3], "value",all_parametres->HDMI_Port_Status);
        cJSON_AddStringToObject(objects[4], "value",all_parametres->Video_Resolution);
        cJSON_AddStringToObject(objects[5], "value",all_parametres->Video_Aspect_Ratio);
        cJSON_AddStringToObject(objects[6], "value",all_parametres->Video_Format);
        cJSON_AddStringToObject(objects[7], "value",all_parametres->Diagnostics_Pages_Language);
        cJSON_AddStringToObject(objects[8], "value",all_parametres->Audio_Setup);
        cJSON_AddStringToObject(objects[9], "value",all_parametres->STB_Lifetime);
        cJSON_AddStringToObject(objects[10], "value",all_parametres->STB_totalPowerOff);
        cJSON_AddStringToObject(objects[11], "value",all_parametres->Time_since_last_STB_boot_up);
        cJSON_AddStringToObject(objects[12], "value",all_parametres->Total_STB_Reboot);
       //parameter
        cJSON_AddStringToObject(objects[0],  "parameter","IR input status");
        cJSON_AddStringToObject(objects[1],  "parameter","Internal temperature");
        cJSON_AddStringToObject(objects[2],  "parameter","CPU utilisation");
        cJSON_AddStringToObject(objects[3],  "parameter","HDMI port status");
        cJSON_AddStringToObject(objects[4],  "parameter","Video resolution");
        cJSON_AddStringToObject(objects[5],  "parameter","Video aspect ratio");
        cJSON_AddStringToObject(objects[6],  "parameter","Video format");
        cJSON_AddStringToObject(objects[7],  "parameter","Diagnostics pages language");
        cJSON_AddStringToObject(objects[8],  "parameter","Audio setup");
        cJSON_AddStringToObject(objects[9],  "parameter","STB lifetime");
        cJSON_AddStringToObject(objects[10], "parameter","STB totalPowerOff");
        cJSON_AddStringToObject(objects[11], "parameter","Time since last STB boot up");
        cJSON_AddStringToObject(objects[12], "parameter","Total STB reboot");
        char* result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"sysInfo\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
      // dynamic parametres
    }else if (strstr(mg_str2pTEXT(&hm->uri),"realTime")) {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //json
        int i;
        
        dynamic_parametres = malloc(sizeof(Dynamic_parametres));
        create_dynamic_parametres(dynamic_parametres);
        
        cJSON *root = cJSON_CreateArray();
        for (i = 0; i < 7; i++){
            cJSON_AddItemToArray(root ,objects[i] = cJSON_CreateObject()); 
        }
        //VALUE
        cJSON_AddStringToObject(objects[0], "value",dynamic_parametres->used_memory);
        cJSON_AddStringToObject(objects[1], "value",dynamic_parametres->Internal_Temperature);
        cJSON_AddStringToObject(objects[2], "value",dynamic_parametres->CPU_Utilisation);
        cJSON_AddStringToObject(objects[3], "value",dynamic_parametres->HDMI_Port_Status);
        cJSON_AddStringToObject(objects[4], "value",dynamic_parametres->stb_ethernet_port_status);
        cJSON_AddStringToObject(objects[5], "value",dynamic_parametres->stb_ip_address);
        cJSON_AddStringToObject(objects[6], "value",dynamic_parametres->total_software_updates);
        //parameter
        cJSON_AddStringToObject(objects[0], "parameter","Used Memory");
        cJSON_AddStringToObject(objects[1], "parameter","Internal temperature");
        cJSON_AddStringToObject(objects[2], "parameter","CPU utilisation");
        cJSON_AddStringToObject(objects[3], "parameter","HDMI port status");
        cJSON_AddStringToObject(objects[4], "parameter","STB ethernet_port_status");
        cJSON_AddStringToObject(objects[5], "parameter","STB IP Address");
        cJSON_AddStringToObject(objects[6], "parameter","Total software updates");

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
