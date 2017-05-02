// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved

#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include "../include/utils/utils.h"


//static
static const char* s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static All_parametres *all_parametres;
static Dynamic_parametres *dynamic_parametres;
static Control_data *control_data;
static Set_parametres *set_parametres;

cJSON *objects[1];

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
