#include "console.h"

//#include "esp_console.h"
//#include "esp_err.h"
#include "dndv_comms.h"

#define PROMPT_STR "DnDevice Master Entry"

void console_init(void){
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    repl_config.prompt = PROMPT_STR "\n>";        //Make this dynamic
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



static int ping_cmd(int argc, char **argv){
    printf("And now we send it!\n");
    send_exampleAwake();
    return 0;
}

esp_err_t ping_r(void){
    esp_console_cmd_t command = {
        .command = "ping",
        .help = "The first data test, with ID 0",
        .func = &ping_cmd
    };
    return esp_console_cmd_register(&command);
}