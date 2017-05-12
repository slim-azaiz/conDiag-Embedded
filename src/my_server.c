// Copyright (c) 2017 AZAIZ SLIM
// All rights reserved
#include <stdlib.h>
#include "dbus/dbus.h"
#include "sc_bus.h"
#include "../include/utils/utils.h"

#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <linux/capability.h>
#include <sys/prctl.h>
#include "libcap.h"
#include <assert.h>

#define USER 	"diagnostic"

//static
static const char* s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static All_parametres *all_parametres;
static Dynamic_parametres *dynamic_parametres;
static Set_parametres *set_parametres;

//drop root privileges
int drop_root_privileges_( const char * const user, size_t cap_nb, const cap_value_t * const cap_list ) 
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

/* User ID to drop to */
#define UID 1006
/* Group ID to drop to */
#define GID 1006

int drop_root_privileges(void)
{
	uid_t real, eff, saved;
	uid_t uid = (uid_t)UID;
	gid_t gid = (gid_t)GID;
	printf("Running as UID %u (effective %u) GID %u (effective %u)\n", getuid(), geteuid(), getgid(), getegid());

	if (setresgid(gid, gid, gid) != 0)
	{
		printf("Failed changing GID to %d with error \n", gid); 
		return -1;
	}
	
	if (setresuid(uid, uid, uid) != 0)
	{
		printf("Failed changing UID to %d with error \n", uid);
		return -1;
	}
	
	if (getresuid(&real, &eff, &saved) != 0)
	{
		printf("Failed reading UID with error \n");
		return -1;
	}
	
	if (real != uid || eff != uid || saved != uid)
	{
		printf("UID sanity check failed\n");
		return -1;
	}

	if (getresgid(&real, &eff, &saved) != 0)
	{
		printf("Failed reading GID with error \n");
		return -1;
	}
	
	if (real != gid || eff != gid || saved != gid)
	{
		printf("GID sanity check failed\n");
		return -1;
	}
	printf("Dropped root privileges. Now running as UID %u GID %u\n", uid, gid);
	return 0;
}

//static Set_data *data;
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
    //resetUsername
    else if (strstr(mg_str2pTEXT(&hm->uri),"/resetUsername")) {
      if(!resetUsername(mg_str2pTEXT(&hm->uri))){
      
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "SUCCESS");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      } else {
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "WRONG OLD USERNAME");
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
      }
    }
    //control
    else if (strstr(mg_str2pTEXT(&hm->uri),"/control")) {
      if(!parseCommand(mg_str2pTEXT(&hm->uri))){
        //execute command
        update_method_value(SET_IR_INPUT_ID, cmd);
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
       // mg_printf_http_chunk(nc, "%s CLICKED \nresultat=%d",cmd,ret);
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
        //set valued
        update_method_value(SET_NETWORK_ID, cmd);
        //print message
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "%s CLICKED \n",cmd);
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
     }
    else if (strstr(mg_str2pTEXT(&hm->uri),"sysInfo")) {
        //sys_info 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"sysInfo\":%s}\n",json(13,30));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"nvmem")) {
        //nvmem 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"nvmem\":%s}\n",json(5,43));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamVirtualTunerStatus")) {
        //virtualTtuner 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
        mg_printf_http_chunk(nc, "{\"qamVirtualTunerStatus\":%s}\n",json(6,48));
        mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */        
    }
    else if (strstr(mg_str2pTEXT(&hm->uri),"qamTunerStatus")) {
        //tuner 
        mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
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


//main
int main(void) {
  
  struct mg_mgr mgr;
  struct mg_connection *nc;
  //all parametres
  all_parametres = malloc(sizeof(All_parametres));
  printf("\nnumber = %s\n",hexdec("00000010")); 
  
  //drop root priveleges

  cap_value_t cap_vals_list[4];
  cap_vals_list[0] = CAP_IPC_LOCK;
  cap_vals_list[1] = CAP_IPC_OWNER;
  cap_vals_list[2] = CAP_NET_RAW;
  cap_vals_list[3] = CAP_NET_BIND_SERVICE;
 
  drop_root_privileges_(USER,4,cap_vals_list);
  //drop_root_privileges();
  prctl (PR_SET_DUMPABLE, 0, 0, 0, 0);
  
   create_all_parametres(all_parametres);
  //control
  create_control_data();
  //init server
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
