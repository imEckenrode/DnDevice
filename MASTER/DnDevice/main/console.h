#pragma once    //May need to do #ifndef "name" define "name" endif if this doesn't work

#include "esp_err.h"
#include "esp_console.h"

/*



*/

void console_init(void);

void register_commands();

//static int ping_cmd(int argc, char **argv);
esp_err_t ping_r(void);
