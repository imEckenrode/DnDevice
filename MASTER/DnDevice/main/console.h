#include "esp_err.h"
#include "esp_console.h"

/*



*/

void console_init(void);

void register_commands();


static int ping_cmd(int argc, char **argv);
esp_err_t ping_r(void){
    esp_console_cmd_t command = {
        .command = "ping",
        .help = "The first data test, with ID 0",
        .func = &ping_cmd
    };
    return esp_console_cmd_register(&command);
}
