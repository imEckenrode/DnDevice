#include <stdio.h>

#include "dndv_internals.h"     //also included: dndv_data
#include "console.h"
#include "dndv_comms.h"
#include "dndv_log.h"
/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
    Any event bases should be added below to DNDV_EBA_DEFINE to add them to the Event Base Array
*/


DNDV_EBA_DEFINE(&SYNC_BASE,
                &DM_SYNC_BASE,
                &MISC_BASE
                );



//  For all initialization of libraries:
void initAll(void){
    nvs_init();         //Initialize the inside file system
    eventLoop_init();   //Initialize the event loop library
    //Initialize the SD card stuff (when needed)
    globals_init();   //Initialize the global variables to the correct values, etc.

    comms_init();       //Initialize the ESP-NOW Communications implementation
    log_init();         //Initialize the logs
    //Initialize the Screen
    console_init();     //Initialize the Console to send commands from a PC
}

//  For everything before the user's first input
void startup(void){
    initAll();              //Initialize all required libraries
    dndv_send_onAwake();    //Send out the "Awake" packet for active DMs to sync
    
    //testDMInit(); 
}

void eba_test(void){
    printf("%d",EventBase2Num(&DM_SYNC_BASE));
    printf("%s",Num2EventBase((Num) 1));
}


/*  And finally, the main entry point of the application  */
void app_main(void)
{
    startup();  //Execute all the required functions that the device doesn't automatically

    eba_test();
}
