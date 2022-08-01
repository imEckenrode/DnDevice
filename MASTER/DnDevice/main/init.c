#include <stdio.h>

#include "dndv_internals.h"
#include "console.h"
#include "dndv_comms.h"
/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
*/

void app_main(void)
{
    nvs_init();
    comms_init();
    //send_exampleAwake();
    console_init();
}
