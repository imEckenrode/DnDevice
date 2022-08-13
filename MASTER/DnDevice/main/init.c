#include <stdio.h>

#include "dndv_internals.h"
#include "console.h"
#include "dndv_comms.h"
#include "dndv_log.h"
/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
*/

//  For all initialization of libraries:
void initAll(void){
    nvs_init();     //Initialize the inside file system
    //Initialize the SD card stuff (when needed)
    comms_init();   //Initialize the ESP-NOW Communications implementation
    log_init();     //Initialize the logs
    //Initialize the Screen
    console_init();     //Initialize the Console to send commands from a PC
}

//  For everything before the user's first input
void startup(void){
    initAll();              //Initialize all required libraries
    dndv_send_onAwake();    //Send out the "Awake" packet for active DMs to sync
}


/*  And finally, the main entry point of the application  */
void app_main(void)
{
    startup();  //Execute all the required functions that the device doesn't automatically
}
