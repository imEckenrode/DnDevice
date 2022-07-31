#include <stdio.h>

#include "console.h"

/*
    init.c
    
    This file is the entry point.
    Anything that needs initialized should be called in app_main
    
*/

void app_main(void)
{
    console_init();
}
