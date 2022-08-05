#include "esp_console.h"






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
    return esp_console_cmd_register(&command);
}




















void register_commands(){
    r_hello();
}

/* STUFF TO DO


*/