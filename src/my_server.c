// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved


#include "../include/data/all_parametres.h"
#include "../include/mongoose/mongoose.h"

#include "string.h"
#include <stdio.h>
#include "../include/cjson/cJSON.h"

typedef struct Auth{
char* username;
char* password;
}Auth;

#define USERNAME "root"
#define PASSWORD "root"

char * usr="";
char * pass="";

cJSON *objects[1];

void parseUsernamePassword(char* string){  
    Auth *auth = malloc(sizeof(Auth));
    usr="";
    pass="";
    char *search = "/";
    char *str = "";
    str = strtok(string,search);
    str = strtok(NULL,search);
    auth->username = str;
    str = strtok(NULL,search);
    auth->password = str;
    if(auth->username!=NULL)
      usr = auth->username;
    if(auth->password!=NULL)
      pass = auth->password;
    printf("%s\n", usr);
    printf("%s\n",pass );
    free(auth);
}


int authentificate(char *string ){
  parseUsernamePassword(string);
    if((strcmp(usr,USERNAME))||(strcmp(pass,PASSWORD)))
        return 0 ;
      else
        return -1;
}

char * mg_str2pTEXT(struct mg_str *mgstr)
{
    char * text = (char *) malloc(mgstr->len + 1);
    strncpy(text, mgstr->p, mgstr->len);
    text[mgstr->len] = '\0';
    return text;
}


static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct http_message *hm = (struct http_message *) p;
  if (ev == MG_EV_HTTP_REQUEST) {
    
    //authentification
    if (strstr(mg_str2pTEXT(&hm->uri),"/authentificate")) {
      if(authentificate(mg_str2pTEXT(&hm->uri))){
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "SUCCESS");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG USERNAME OR PASSWORD");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    }
    //diagnostic
    else if (strstr(mg_str2pTEXT(&hm->uri),"diag")) {
        //all parametres
        All_parametres *all_parametres = malloc(sizeof(All_parametres));
        create_all_parametres(all_parametres);
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
        cJSON_AddStringToObject(objects[0], "parameter","serial_number");
        cJSON_AddStringToObject(objects[1], "parameter","nagra_serial_number");
        cJSON_AddStringToObject(objects[2], "parameter","model");
        cJSON_AddStringToObject(objects[3], "parameter","stb_mac_address");
        cJSON_AddStringToObject(objects[4], "parameter","ethernet_mac_address");
        cJSON_AddStringToObject(objects[5], "parameter","firmware_version");
        cJSON_AddStringToObject(objects[6], "parameter","network_id");
        cJSON_AddStringToObject(objects[7], "parameter","manufacturer");
        //conditional_access
        cJSON_AddStringToObject(objects[8], "parameter","Nagra_Serial_Number");
        cJSON_AddStringToObject(objects[9], "parameter","CA_Provider_Name");
        //loader_data
        cJSON_AddStringToObject(objects[10], "parameter","boot_loader_version");
        cJSON_AddStringToObject(objects[11], "parameter","boot_loader_crc");
        //memoire_data
        cJSON_AddStringToObject(objects[12], "parameter","memory_block_status");
        cJSON_AddStringToObject(objects[13], "parameter","used_memory");
        cJSON_AddStringToObject(objects[14], "parameter","total_memory");
        cJSON_AddStringToObject(objects[15], "parameter","addressing_memory");
        //network_data
        cJSON_AddStringToObject(objects[16], "parameter","stb_serial_number");
        cJSON_AddStringToObject(objects[17], "parameter","manufacturer");
        cJSON_AddStringToObject(objects[18], "parameter","stb_ip_address");
        cJSON_AddStringToObject(objects[19], "parameter","stb_mac_ethernet");
        cJSON_AddStringToObject(objects[20], "parameter","stb_ethernet_port_status");
        cJSON_AddStringToObject(objects[21], "parameter","dns_serverII");
        cJSON_AddStringToObject(objects[22], "parameter","stb_ip_default_gateway");
        cJSON_AddStringToObject(objects[23], "parameter","stb_subnet_mask");
        //software_data
        cJSON_AddStringToObject(objects[24], "parameter","tivo_software_name");
        cJSON_AddStringToObject(objects[25], "parameter","date_time_last_stb_software");
        cJSON_AddStringToObject(objects[26], "parameter","total_software_updates");
        //sys_info 
        cJSON_AddStringToObject(objects[27], "parameter","IR_Input_Status");
        cJSON_AddStringToObject(objects[28], "parameter","Internal_Temperature");
        cJSON_AddStringToObject(objects[29], "parameter","CPU_Utilisation");
        cJSON_AddStringToObject(objects[30], "parameter","HDMI_Port_Status");
        cJSON_AddStringToObject(objects[31], "parameter","Video_Resolution");
        cJSON_AddStringToObject(objects[32], "parameter","Video_Aspect_Ratio");
        cJSON_AddStringToObject(objects[33], "parameter","Video_Format");
        cJSON_AddStringToObject(objects[34], "parameter","Diagnostics_Pages_Language");
        cJSON_AddStringToObject(objects[35], "parameter","Audio_Setup");
        cJSON_AddStringToObject(objects[36], "parameter","STB_Lifetime");
        cJSON_AddStringToObject(objects[37], "parameter","STB_totalPowerOff");
        cJSON_AddStringToObject(objects[38], "parameter","Time_since_last_STB_boot_up");
        cJSON_AddStringToObject(objects[39], "parameter","Total_STB_Reboot");
        char *result = cJSON_Print(root);
        mg_printf_http_chunk(nc, "{\"diagnostics\":%s}\n",result);

        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        free(all_parametres);
      }
    mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
  }
}



int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;

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
