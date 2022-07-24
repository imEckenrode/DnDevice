#include <stdio.h>
#include "esp_console.h"

#include "the_functions.h"

#include "esp_err.h"


//static const char* TAG = "DnDevice";
#define PROMPT_STR "DnDevice"





static int hello_cmd(int argc, char **argv){
    printf("\nHello there! I am the working command line system!\n");
    return 0;
}   //The actual commands should be accessible to both the command line and the communication system


esp_err_t r_hello(void){
    esp_console_cmd_t command = {
        .command = "hello",
        .help = "Talk a little bit to the device (Test Numero Uno)",
        .func = &hello_cmd
    };
    return esp_console_cmd_register(&command);          //I feel like I could register everything in the same place
}


void register_commands(){
    r_hello();
}




void console_init(void)
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    repl_config.prompt = PROMPT_STR ">";        //Make this dynamic
    repl_config.max_cmdline_length = 1024; //CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH; from sdkconfig, idk

    register_commands();


    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}
