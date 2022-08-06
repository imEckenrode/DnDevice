#pragma once    //May need to do #ifndef "name" define "name" endif if this doesn't work

#include "esp_err.h"
#include "esp_console.h"

/*

    Not much is needed in this file, as everything is done internally

*/

//  Initialize console
void console_init(void);

//  This command registers all the console commandsss
void register_commands();

