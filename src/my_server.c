// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <linux/capability.h>
#include <sys/prctl.h>
#include <assert.h>

#include "dbus/dbus.h"
#include "sc_bus.h"
#include "utils/utils.h"
#include "libcap.h"

/**********************************************************************************
*						              DEFINES
**********************************************************************************/
#define USER                	"diagnostic"
#define s_http_port             "8000"
/*-----------------------------------------------------------------------------
					STATIC VARIABLES       
-----------------------------------------------------------------------------*/
static struct mg_serve_http_opts s_http_server_opts;



/**********************************************************************************
*						              FUNCTIONS
**********************************************************************************/


static int drop_root_privileges( const char * const user, size_t cap_nb, const cap_value_t * const cap_list ) 
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
        char* username;
        char* password;
        parseUsernamePassword(mg_str2pTEXT(&hm->uri),&username,&password);
        if(authentificate(username,password) == RESULT_SUCCESS){
            //load all parametres
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
        if (username != NULL)
            free(username);
        if (password != NULL)
            free(password);
    }
   
    //resetPassword
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetPassword")) {
		char* oldPassword;
		char* newPassword;
        parseNewOldParameter(mg_str2pTEXT(&hm->uri),&oldPassword,&newPassword);
        if(!resetPassword(oldPassword,newPassword)){
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "SUCCESS");
            mg_send_http_chunk(nc, "", 0);  
        } else {
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "WRONG OLD PASSWORD");
            mg_send_http_chunk(nc, "", 0);  
        }
        if (oldPassword != NULL)
            free(oldPassword);
        if (newPassword != NULL)
            free(newPassword);
    }
    //resetUsername
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetUsername")) {
		char* oldUsername;
		char* newUsername;
        parseNewOldParameter(mg_str2pTEXT(&hm->uri),&oldUsername,&newUsername);
        if(!resetUsername(oldUsername,newUsername)){ 
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "SUCCESS");
            mg_send_http_chunk(nc, "", 0);  
        } else {
            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
            mg_printf_http_chunk(nc, "WRONG OLD USERNAME");
            mg_send_http_chunk(nc, "", 0);  
        }
        if (oldUsername != NULL)
            free(oldUsername);
        if (newUsername != NULL)
            free(newUsername);
    }
    //control
    else if (strstr(mg_str2pTEXT(&hm->uri),"/control")) {
        char *controlKey;
        parseCommand(mg_str2pTEXT(&hm->uri),&controlKey);
        //execute command
        update_method_value(SET_IR_INPUT_ID,controlKey);
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        printf("\n%s ",controlKey);
        mg_send_http_chunk(nc, "", 0);  
        if (controlKey != NULL)
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
        
            mg_send_http_chunk(nc, "", 0);  
       
        
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
        mg_send_http_chunk(nc, "", 0);  
      }
        free(newOldParameter);
    }
    #endif
    //diagnostic static parametres
    else if (strstr(mg_str2pTEXT(&hm->uri),"diagnostic")) {
        //all parametres
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"diagnostic\":[] }\n");
        mg_send_http_chunk(nc, "", 0);  
    }else if (strstr(mg_str2pTEXT(&hm->uri),"realTime")) {
    // dynamic parametres
        char* interface;char* result_realtime;
        parseCommand(mg_str2pTEXT(&hm->uri),&interface);
        if(!strcmp(interface,"memory")){
            json_memory_real_time(&result_realtime);
        }else if(!strcmp(interface,"software")){
            json_software_real_time(&result_realtime);
        }else if(!strcmp(interface,"sysInfo")){
            json_sys_info_real_time(&result_realtime);
        }else if(!strcmp(interface,"network")){
            json_network_real_time(&result_realtime);
        }
        
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"realTime\":%s}\n",result_realtime);
        mg_send_http_chunk(nc, "", 0);  
        
        if (interface != NULL)
            free(interface);
    }else if (strstr(mg_str2pTEXT(&hm->uri),"identification")) {
    // stb_identification      
        char* result_identification;
        json_stb_identification(&result_identification);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"identification\":%s}\n",result_identification);
        mg_send_http_chunk(nc, "", 0);  
        if(result_identification != NULL)
            free(result_identification);
    }else if (strstr(mg_str2pTEXT(&hm->uri),"conditionalAccess")) {
    //conditional_access
        char* result_conditional_access;
        json_conditional_access(&result_conditional_access);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"conditional\":%s}\n",result_conditional_access);
        mg_send_http_chunk(nc, "", 0);  
        if(result_conditional_access != NULL)
            free(result_conditional_access);
    }else if (strstr(mg_str2pTEXT(&hm->uri),"memory")) {
    //memoire_data
        char* result_memory;
        json_memory(&result_memory);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"memory\":%s}\n",result_memory);
        mg_send_http_chunk(nc, "", 0);  
        if(result_memory != NULL)
            free(result_memory);
     }else if (strstr(mg_str2pTEXT(&hm->uri),"loader")) {
    //loader_data
        char* result_loader;
        json_loader(&result_loader);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"loader\":%s}\n",result_loader);
        mg_send_http_chunk(nc, "", 0);  
        if(result_loader != NULL)
            free(result_loader);
     }else if (strstr(mg_str2pTEXT(&hm->uri),"software")) {
    //software_data
		char* result_software;
		json_software(&result_software);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"software\":%s}\n",result_software);
        mg_send_http_chunk(nc, "", 0);
        if(result_software != NULL)
			free(result_software);
     }else if (strstr(mg_str2pTEXT(&hm->uri),"network")) {
    //network_data
        char* result_network;
        json_network(&result_network);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"network\":%s}\n",result_network);
        mg_send_http_chunk(nc, "", 0);  
        if(result_network != NULL)
            free(result_network);
     }
    else if (strstr(mg_str2pTEXT(&hm->uri),"sysInfo")) {
    //sys_info 
        char* result_sys_info;
        json_sys_info(&result_sys_info);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"sysInfo\":%s}\n",result_sys_info);
        mg_send_http_chunk(nc, "", 0);          
        if(result_sys_info != NULL)
            free(result_sys_info);
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"nvmem")) {
    //nvmem 
        char* result_nvmem;
        json_nvmem(&result_nvmem);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"nvmem\":%s}\n",result_nvmem);
        mg_send_http_chunk(nc, "", 0);          
        if(result_nvmem != NULL)
            free(result_nvmem);
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamVirtualTunerStatus")) {
    //virtualTtuner 
        char* result_virtual_tuner;
        json_virtual_tuner(&result_virtual_tuner);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"qamVirtualTunerStatus\":%s}\n",result_virtual_tuner);
        mg_send_http_chunk(nc, "", 0);          
        if(result_virtual_tuner != NULL)
            free(result_virtual_tuner);
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamTunerStatus")) {
     //tuner
        char* result_tuner; 
        json_tuner(&result_tuner);
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"qamTunerStatus\":%s}\n",result_tuner);
        mg_send_http_chunk(nc, "", 0);          
        if(result_tuner != NULL)
            free(result_tuner);
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
  
  //drop root priveleges
  cap_value_t cap_vals_list[4];
  cap_vals_list[0] = CAP_IPC_LOCK;
  cap_vals_list[1] = CAP_IPC_OWNER;
  cap_vals_list[2] = CAP_NET_RAW;
  cap_vals_list[3] = CAP_NET_BIND_SERVICE;
  drop_root_privileges(USER,4,cap_vals_list);
  prctl (PR_SET_DUMPABLE, 0, 0, 0, 0);
  
 
  //control
  //Set_data *data = malloc(sizeof(Set_data));
 
 //init scbus
  init_sc_bus();
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
  deinit_sc_bus();
  mg_mgr_free(&mgr);
  return 0;
  
}
