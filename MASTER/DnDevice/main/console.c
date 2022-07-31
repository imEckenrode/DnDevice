#include "esp_console.h"
#include "esp_err.h"



#define PROMPT_STR "DnDevice"

void console_init(void){
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    repl_config.prompt = PROMPT_STR ">";        //Make this dynamic
    repl_config.max_cmdline_length = 1024; //CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH; from sdkconfig, idk

    register_commands();

    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));  //Gonna need a thread for this
}

/*  Register all the console commands
        the r is for register (found in header file)    */
void register_commands(){
    ping_r();       
    //Can also check for errors here if desired
}

/* --- Console Command Definitions --- */

static int ping_cmd(int argc, char **argv){
    printf("And now we send it!");
    return 0;
}