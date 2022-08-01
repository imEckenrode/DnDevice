#include <stdio.h>

#include "console.h"
#include "dndv_comms.h"
/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
*/

void app_main(void)
{
    comms_init();
    send_exampleAwake();
    console_init();
}
