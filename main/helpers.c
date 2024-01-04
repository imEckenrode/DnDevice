#include "helpers.h"
//This isn't found for some reason...that's why screen_actions.c has a duplicate
#include "stdlib.h"
#include "esp_log.h"

long int stringToLong(char* input){
    char *leftovers;
    long num = strtol(input, &leftovers, 10);

    //This stops at the first character that is not a digit, plus, minus, or whitespace
    //Could check for garbage/success by looking at leftovers

    if(*leftovers!='\0'){
        ESP_LOGE("DnDevice", "Could not parse full string to number!");

        //TODO: throw an error
    }

    return num;
}