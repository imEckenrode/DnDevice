#include "console.h"

//#include "esp_console.h"
//#include "esp_err.h"
#include "dndv_comms.h"
#include "dndv_internals.h"
#include "dndv_sync.h"

#define PROMPT_STR "\nDnDevice Console"


static int ping_cmd(int argc, char **argv){
    printf("And now we send it!\n");
    dndv_send_ping();
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




/*  Temporary testing commands  */

//Activate the test GM account
static int testGM_cmd(int argc, char **argv){
    testGMInit();
    update_comms_sync_mode(true);
    dndv_send_broadcast(N_SYNC_BASE,EVENT_GM_INFO,&current.gmInfo,sizeof(struct gmInfo));
    return 0;
}
esp_err_t testGM_r(void){
    esp_console_cmd_t command = {
        .command = "keyin-GM",
        .help = "Activate a test GM account",
        .func = &testGM_cmd
    };
    return esp_console_cmd_register(&command);
}

//Activate the test Player account
static int testPC_cmd(int argc, char **argv){
    testPCInit();
    update_comms_sync_mode(false);          //TODO: Build this into the activate function. LISTEN FOR IT WITH DNDV_SYNC.
    return 0;
}
esp_err_t testPC_r(void){
    esp_console_cmd_t command = {
        .command = "keyin-PC",
        .help = "Activate a test player account (with a character selected)",
        .func = &testPC_cmd
    };
    return esp_console_cmd_register(&command);
}

static int tellMeYourNameAgain_cmd(int argc, char **argv){  //TODO: Update to work with GM
    printf("Active Player: %s\nActive PC: %s\n", current.my->Player.name, current.my->PC.name);
    //Alternatively, current.player->name,current.character->name
    return 0;
}
esp_err_t tellMeYourNameAgain_r(void){
    esp_console_cmd_t command = {
        .command = "nameis",
        .help = "Print the active player and character name",
        .func = &tellMeYourNameAgain_cmd
    };
    return esp_console_cmd_register(&command);
}


//Now for enabling and disabling logs
static int logsOn_cmd(int argc, char **argv){
    current.settings.displayLogs = true;
    printf("Logs Enabled\n");
    return 0;
}
esp_err_t logsOn_r(void){
    esp_console_cmd_t command = {
        .command = "logson",
        .help = "Enables logs printing",
        .func = &logsOn_cmd
    };
    return esp_console_cmd_register(&command);
}

static int logsOff_cmd(int argc, char **argv){
    current.settings.displayLogs = false;
    printf("Logs Disabled\n");
    return 0;
}
esp_err_t logsOff_r(void){
    esp_console_cmd_t command = {
        .command = "logsoff",
        .help = "Disables logs printing",
        .func = &logsOff_cmd
    };
    return esp_console_cmd_register(&command);
}

//And finally...
/*  Register all the console commands   */
void register_commands(){
    ping_r();
    testGM_r();
    testPC_r();
    tellMeYourNameAgain_r();

    logsOn_r();
    logsOff_r();
    //Could also check for errors here if desired
}


//Initialize the console
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