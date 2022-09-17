#include <stdio.h>
#include "esp_console.h"

#include "cliCommands.h"

#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_err.h"

//static const char* TAG = "DnDevice";
#define PROMPT_STR "Test"

void nvs_init(void){
    esp_err_t ret = nvs_flash_init();   //Initialize the nvs, and use "ret"urn to clear out if more space is needed
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main(void)
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
