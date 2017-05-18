// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved
#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include "utils/utils.h"

#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <linux/capability.h>
#include <sys/prctl.h>
#include "libcap.h"
#include <assert.h>

/**********************************************************************************
*						              DEFINES
**********************************************************************************/

#define USER 	"diagnostic"
//#define UID 1006
//#define GID 1006
/*-----------------------------------------------------------------------------
					STATIC VARIABLES       
-----------------------------------------------------------------------------*/
static const char* s_http_port = "8000"; /*  define*/
static struct mg_serve_http_opts s_http_server_opts;/* tester local si non global*/

static All_parametres *all_parametres;
static Dynamic_parametres *dynamic_parametres;

cJSON *objects[1];//supprimer



int drop_root_privileges( const char * const user, size_t cap_nb, const cap_value_t * const cap_list ) 
{
	cap_t       caps;
	cap_value_t cap_vals_list[CAP_LAST_CAP+2];
	struct passwd *pwd = NULL;
	struct group *grp = NULL;
	int ngrp = 0;
	gid_t *grps = NULL;
	register uid_t uid;
	register gid_t gid;
	uid_t ru, eu, su;
	gid_t rg, eg, sg;
	int ret, i;

	assert (NULL != user);

	if(cap_nb > 0)
	{
		assert (NULL != cap_list);
		assert ( CAP_LAST_CAP > cap_nb);
		caps = cap_get_proc();
		assert (NULL != caps);
		ret = cap_clear(caps); /* drop all capabilities*/
		assert (0 == ret);

		for( i = 0; i < cap_nb; i++ ) 
		{
			cap_vals_list[i] = cap_list[i];
		}
		cap_vals_list[cap_nb] = CAP_SETGID;
		cap_vals_list[cap_nb+1] = CAP_SETUID;
		ret = cap_set_flag(caps, CAP_PERMITTED, cap_nb+2, cap_vals_list, CAP_SET);		
		assert(0 == ret);
		ret = cap_set_flag(caps, CAP_EFFECTIVE, cap_nb+2, cap_vals_list, CAP_SET);
		assert(0 == ret);
		ret = cap_set_proc(caps);
		assert(0 == ret);
		ret = cap_free(caps);
		assert(-1 != ret);
		ret = prctl(PR_SET_KEEPCAPS,1);
		assert(-1 != ret);
	}
	pwd = getpwnam (user);
	assert (NULL != pwd);
	uid = pwd->pw_uid;
	grp = getgrnam (user);
	assert (NULL != grp);
	gid = grp->gr_gid;
	getgrouplist(user, gid, grps, &ngrp);
  
	if (ngrp > 0)
	{
		grps = alloca (sizeof (gid_t) * ngrp);
		ret = getgrouplist (user, gid, grps, &ngrp);
		assert (-1 != ret);
		ret = setgroups(ngrp, grps);
		assert (0 == ret);
	}

	do
	{
		ret = setresgid (gid, gid, gid);
		assert (0 == ret);
		ret = setresuid (uid, uid, uid);
		assert (0 == ret);
		ret = getresgid (&rg, &eg, &sg);
		assert (0 == ret);
		ret = getresuid (&ru, &eu, &su);
		assert (0 == ret);
	} while (  uid != ru || uid != eu || uid != su || gid != rg || gid != eg || gid != sg);

	if(cap_nb > 0)
	{
		caps = cap_get_proc();
		assert (NULL != caps);
		ret = cap_set_flag(caps, CAP_EFFECTIVE, cap_nb, cap_list, CAP_SET);
		assert(-1 != ret);
		ret = cap_set_proc(caps);
		assert(-1 != ret);
		ret = cap_free(caps);
		assert(-1 != ret);
	}
	printf("Dropped root privileges. Now running as UID %u GID %u\n", uid, gid);
	return 0;
}


/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : ev_handler
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : assign cjonn objects  
 * Return type   : void
 * Argument      : nb:In
                   index:In
 **********************************************************************/
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


/***********************************************************************
 *                     *** Copyright (C) 2017 SAGEMCOM SA ***
 * Function name : ev_handler
 * Author        : AZAIZ SLIM
 * Creation date : 2017-05-15
 * Description   : Each connection has an event handler function 
                    associated with it. Event handler is the key element
                    of the Mongoose application, since it defines the
                    application's behaviour.  
 * Return type   : void
 * Argument      : ev: Out
                   p:In
                   mg_connection:In
                   
 **********************************************************************/
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct http_message *hm = (struct http_message *) p;
  if (ev == MG_EV_HTTP_REQUEST) {
    //authentification
    if (strstr(mg_str2pTEXT(&hm->uri),"/authentificate")) {
        Auth auth;
        parseUsernamePassword(mg_str2pTEXT(&hm->uri),auth);
        //printf("result = %d",authentificate(mg_str2pTEXT(&hm->uri)));
      if(authentificate(auth)){
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
      // free(auth);
    }
    //resetPassword
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetPassword")) {
		char* username;
		char* password;
		
        NewOldParameter *newOldParameter = malloc(sizeof(NewOldParameter));
       // parseNewOldParameter(mg_str2pTEXT(&hm->uri),newOldParameter);
        parseNewOldParameter(mg_str2pTEXT(&hm->uri),username,password);
        if(!resetPassword(newOldParameter)){
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "SUCCESS");
            mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        } else {
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "WRONG OLD PASSWORD");
            mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        }
        if (username != NULL)
        free(username)
        if (password != NULL)
        free(password)
        free(newOldParameter);
    }
    //resetUsername
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetUsername")) {
        NewOldParameter newOldParameter;
        parseNewOldParameter(mg_str2pTEXT(&hm->uri),newOldParameter);
        if(!resetUsername(newOldParameter)){ 
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "SUCCESS");
            mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        } else {
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "WRONG OLD USERNAME");
            mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        }
       // free(newOldParameter);
    }
    //control
    else if (strstr(mg_str2pTEXT(&hm->uri),"/control")) {
        //char *controlKey = (char*) malloc(12*sizeof(char));
        char *controlKey =  malloc(sizeof(char)*50);
        parseCommand(mg_str2pTEXT(&hm->uri), controlKey);
        //execute command
        update_method_value(SET_IR_INPUT_ID, controlKey);
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        printf("\n%s ",controlKey);
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
        free(controlKey);
    } 
    //set parametres
    #if 0
    else if (strstr(mg_str2pTEXT(&hm->uri),"/set")) {
        NewOldParameter *newOldParameter = malloc(sizeof(NewOldParameter));
        parseNewOldParameter(mg_str2pTEXT(&hm->uri),newOldParameter);
        if (strcmp(newOldParameter->oldParameter,"NETWORK_ID")==0) {
                update_method_value(SET_NETWORK_ID, newOldParameter->newParameter);
            }
        else if (strcmp(newOldParameter->oldParameter,"TCD_MODE")==0) {
            update_method_value(SET_TCD_MODE, newOldParameter->newParameter);
            get_nvmem_parametres(all_parametres);
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            cJSON *root = cJSON_CreateArray();
            cJSON_AddItemToArray(root ,objects[0] = cJSON_CreateObject()); 
            cJSON_AddStringToObject(objects[0], "value",all_parametres->members[43][0]);
            cJSON_AddStringToObject(objects[0], "parameter",all_parametres->members[43][1]);
            char* result = cJSON_Print(root);
            mg_printf_http_chunk(nc, "{\"dataToSet\":%s}\n",result);
        
            mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
       
        
        } 
        else if (strcmp(newOldParameter->oldParameter,"SI_MILTICAST_ADDRESS")==0) {
            update_method_value(SET_SI_MILTICAST_ADDRESS, newOldParameter->newParameter);
        } 
        else if (strcmp(newOldParameter->oldParameter,"VM_INSTALLER_FREQUENCY")==0) {
            update_method_value(SET_VM_INSTALLER_FREQUENCY, newOldParameter->newParameter);
        } 
        else if (strcmp(newOldParameter->oldParameter,"VM_INSTALLER_SYMBOLRATE")==0) {
            update_method_value(SET_VM_INSTALLER_SYMBOLRATE, newOldParameter->newParameter);
        } 
        else if (strcmp(newOldParameter->oldParameter,"VM_INSTALLER_MODULATION")==0) {
            update_method_value(SET_VM_INSTALLER_MODULATION, newOldParameter->newParameter);
        } 
        else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG PARAMETER");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
        free(newOldParameter);
    }
    #endif
    //diagnostic static parametres
    else if (strstr(mg_str2pTEXT(&hm->uri),"diagnostic")) {
        //all parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"identification")) {
    // stb_identification      
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_stb_identification_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"identification\":%s}\n",json(10,0));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"conditionalAccess")) {
    //conditional_access
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_conditional_access_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"conditional\":%s}\n",json(2,10));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    }else if (strstr(mg_str2pTEXT(&hm->uri),"memory")) {
    //memoire_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_memory_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"memory\":%s}\n",json(4,14));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"loader")) {
    //loader_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_loader_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"loader\":%s}\n",json(2,12));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"software")) {
    //software_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_software_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"software\":%s}\n",json(4,26));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }else if (strstr(mg_str2pTEXT(&hm->uri),"network")) {
    //network_data
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_network_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"network\":%s}\n",json(8,18));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
     }
    else if (strstr(mg_str2pTEXT(&hm->uri),"sysInfo")) {
    //sys_info 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_sys_info_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"sysInfo\":%s}\n",json(13,30));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"nvmem")) {
    //nvmem 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_nvmem_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"nvmem\":%s}\n",json(5,43));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamVirtualTunerStatus")) {
    //virtualTtuner 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_virtual_tuner_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"qamVirtualTunerStatus\":%s}\n",json(6,48));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamTunerStatus")) {
     //tuner 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        //get_tuner_parametres(all_parametres);
        mg_printf_http_chunk(nc, "{\"qamTunerStatus\":%s}\n",json(18,54));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"realTime")) {
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


 /*******************************************************************
* NAME :            int main()
*
* DESCRIPTION :     Entry function of conDiag program
*
* INPUTS :
*       PARAMETERS:
*           None
* OUTPUTS :
*       PARAMETERS:
*           None
*       RETURN :
*            Type:   int                    Error code:
*            Values: "-1"             		If one of the called function failed
*                    "0"                    Success            			
* PROCESS :
*                   [1]  Drop all privileges except the CAP_IPC_LOCK/CAP_IPC_OWNER/CAP_DAC_OVERRIDE/CAP_SETGID/CAP_SETUID 
* 					     privileges for conDiag (Container/NASC related requirement)
*                   [2]  Init first sc_bus (dbus based library developped by Sagemcom)
*                   [3]  Init second sc_bus for exchange with TR69 (dbus based library developped by Sagemcom)
*                   [4]  Gather diagnostic parametres from Gather program and assign them to json objects 
*                   [5]  Init Mongoose web server 
*                   [6]  Set  diagnostic parametres if asked
*                   [7]  Infinit loop to handle other process requests
* 					[8] Un-init
*
* NOTES :           
*/
int main() {
  
  struct mg_mgr mgr;
  struct mg_connection *nc;
  //all parametres
  all_parametres = malloc(sizeof(All_parametres));
  
  //drop root priveleges
  cap_value_t cap_vals_list[4];
  cap_vals_list[0] = CAP_IPC_LOCK;
  cap_vals_list[1] = CAP_IPC_OWNER;
  cap_vals_list[2] = CAP_NET_RAW;
  cap_vals_list[3] = CAP_NET_BIND_SERVICE;
  drop_root_privileges(USER,4,cap_vals_list);
  prctl (PR_SET_DUMPABLE, 0, 0, 0, 0);
  
 
  create_all_parametres(all_parametres);
  //control
  Set_data *data = malloc(sizeof(Set_data));
  create_set_data();/*renommer la fonction*/
  //load parametres
  get_stb_identification_parametres(all_parametres);
  get_conditional_access_parametres(all_parametres);
  get_memory_parametres(all_parametres);
  get_loader_parametres(all_parametres);
  get_software_parametres(all_parametres);
  get_network_parametres(all_parametres);
  get_nvmem_parametres(all_parametres);
  get_tuner_parametres(all_parametres);
  get_virtual_tuner_parametres(all_parametres);
  get_sys_info_parametres(all_parametres);
  
  //init server
  mg_mgr_init(&mgr, NULL);
  printf("[ConDiag][%s]Starting web server on port %s\n",__FUNCTION__, s_http_port);

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
