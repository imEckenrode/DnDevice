#include <stdio.h>

#include "device.h"
#include "data_pc.h"
#include "sd_card.h"
#include "screen_control.h"
/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
*/




//  For all initialization of libraries:
void initAll(void){
    nvs_init();         //Initialize the inside file system
    eventLoop_init();   //Initialize the event loop library and our event loops

    ui_stuff_init();

    //sd_card_init();

}

//  For everything before the user's first input
void startup(void){
    initAll();              //Initialize all required libraries

    default_pc_init();

    //refresh the screen here
    //ui_refresh(true); gonna have to wait a bit before running this (most likely done in the screen itself)
}


/*  And finally, the main entry point of the application  */
void app_main(void)
{
    startup();  //Execute all the required functions that the device doesn't automatically
}
