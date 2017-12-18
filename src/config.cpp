/*
 * config.cpp
 *
 *  Created on: 14.11.2017
 *      Author: user
 */

#include "/usr/include/libconfig.h"
#include <iostream>
#include "config.h"
#include <stdio.h>
config_t cfg, *cf;;
config_setting_t *array;
//  config_setting_add
  char *config_file_name = "config.cfg";
config_setting_t *retries,*setting,*root;
  int count, n, enabled;
 void config::init() {

	config_init(&cfg);
	if (!config_read_file(&cfg, config_file_name))
	    {

	        config_write_file(&cfg, config_file_name);
	       if (!config_read_file(&cfg, config_file_name)) {
	    	   printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
	       }

	    }
	  root = config_root_setting(&cfg);
	 cf = &cfg;
	 retries = config_lookup(cf, "Mousecommands");

if (!(retries)) {
		int i;
	//	 printf("e");

		 array = config_setting_add(root, "Mousecommands", CONFIG_TYPE_ARRAY);
		  for(i = 0; i < 12; ++i)
		  {
		    setting = config_setting_add(array, NULL, CONFIG_TYPE_STRING);
		    config_setting_set_string(setting, "/bin/test");
		  }



		  if(!( config_write_file(&cfg, config_file_name))){
				      printf( "Nie można zapisać błąd.\n");
				      config_destroy(&cfg);

				    }


	}




 }

char* config::readmouse(int mouse) {
	 retries = config_lookup(cf, "Mousecommands");
	 if (!(mouse < 0)) {
	 	if (!(mouse > 12)) {

	 		return	(char*)config_setting_get_string_elem(retries, mouse);
	 	}}
return "error";
}

bool config::writemouse(int mouse,char* code) {

	 	 retries = config_lookup(cf, "Mousecommands");
	 	 if (!(mouse < 0)) {
	 	 	if (!(mouse > 12)) {

	 	 		config_setting_set_string_elem(retries, mouse,code);

	 	 		return config_write_file(&cfg, config_file_name);
	 	 	}}

return false;
 }



