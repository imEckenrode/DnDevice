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

#include "argtable3/argtable3.h"
static struct {
    struct arg_str *say;
    struct arg_end *end;
} args;


static int say_cmd(int argc, char **argv){
    int nerrors = arg_parse(argc, argv, (void **) &args);
    if (nerrors != 0) {
        arg_print_errors(stderr, args.end, argv[0]);
        return 1;
    }
    printf("\n%s\n",args.say->sval[0]);

    return 0;
}   //The actual commands should be accessible to both the command line and the communication system



esp_err_t r_say(void){
    args.say = arg_str0(NULL, NULL, "<this>", "Stuff To Say");
   args.end = arg_end(2);

    esp_console_cmd_t command = {
        .command = "say",
        .help = "Prints inputs (For testing arguments)",
        .func = &say_cmd,
        .argtable = &args
    };
    return esp_console_cmd_register(&command);
}



void register_commands(){
    r_hello();
    r_say();
}

/* STUFF TO DO


*/