// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved


#include "../include/data/stb_identification_data.h"
#include "../include/data/network_data.h"
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
        //stb identification
        Stb_identification_data *stb_identification_data = malloc(sizeof(Stb_identification_data));
        create_Stb_identification_data(stb_identification_data);
        //network data 
        Network_data *network_data = malloc(sizeof(Network_data));
        create_network_data(network_data);
        //conditional access
        //software data
        //system information
        //memoire information
        //loader 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
       

        //json
        cJSON *diag;
        cJSON *obj1;
        cJSON *obj2;
        diag = cJSON_CreateObject();
        cJSON_AddItemToObject(diag, "Stb_identification_data", obj1 = cJSON_CreateObject());
        cJSON_AddItemToObject(diag, "network_data", obj2 = cJSON_CreateObject());
        cJSON_AddStringToObject(obj1, "serial_number", stb_identification_data->serial_number);
        cJSON_AddStringToObject(obj1, "serial_number",stb_identification_data->serial_number);
        cJSON_AddStringToObject(obj1, "nagra_serial_number",stb_identification_data->nagra_serial_number);
        cJSON_AddStringToObject(obj1, "model",stb_identification_data->model);
        cJSON_AddStringToObject(obj1, "stb_mac_address",stb_identification_data->stb_mac_address);
        cJSON_AddStringToObject(obj1, "ethernet_mac_address",stb_identification_data->ethernet_mac_address);
        cJSON_AddStringToObject(obj1, "firmware_version",stb_identification_data->firmware_version);
        cJSON_AddStringToObject(obj1, "network_id",stb_identification_data->network_id);
        cJSON_AddStringToObject(obj1, "manufacturer",stb_identification_data->manufacturer);
    
        cJSON_AddStringToObject(obj2, "stb_subnet_mask",network_data->stb_subnet_mask);
        cJSON_AddStringToObject(obj2, "stb_ip_default_gateway",network_data->stb_ip_default_gateway);
        cJSON_AddStringToObject(obj2, "dns_serverII",network_data->dns_serverII);
        cJSON_AddStringToObject(obj2, "stb_ethernet_port_status",network_data->stb_ethernet_port_status);
        cJSON_AddStringToObject(obj2, "stb_mac_ethernet",network_data->stb_mac_ethernet);
        cJSON_AddStringToObject(obj2, "stb_ip_address",network_data->stb_ip_address);
        cJSON_AddStringToObject(obj2, "stb_mac_address",network_data->stb_mac_address);
        cJSON_AddStringToObject(obj2, "stb_serial_number",network_data->stb_serial_number);
       
        char *result = cJSON_Print(diag);
        mg_printf_http_chunk(nc, "%s\n",result);


        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        free(network_data);
        free(stb_identification_data);
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
